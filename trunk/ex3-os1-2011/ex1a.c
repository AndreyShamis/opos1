#include <stdio.h>
#include <string.h>
#include "shell.h"

struct rusage u_rusage;
int status ;

int grp_id;


//================== Catch exit Handler =======================================
void catch_chld(pid_t num)
{

	wait4(-1,&status,WNOHANG,&u_rusage) ;
	//while(> 0)
	//{
		//;
		//getrusage(num,&u_rusage);
		//printf("lol\n Status:%d\n Num %d\n",status,num);
	//}
	long sys_time = u_rusage.ru_stime.tv_sec;
	long sys_timeu =  u_rusage.ru_stime.tv_usec;
	long usr_time = u_rusage.ru_utime.tv_sec;
	long usr_timeu =  u_rusage.ru_utime.tv_usec;
	int exit_stat= status;
	printf("%ld.%06ld ,%ld.%06ld ,%d\n",sys_time,sys_timeu,usr_time,usr_timeu,exit_stat);
	
}

//=============================================================================
void print_arr_t(char **data,const int size)
{
	int i=0,x=0;


	printf("PRINT SIZE: %d\n",size);
	
	for(i=0;i<size;i++)
	{
		if(data[i] != NULL)
		{
			for(x=0;x<strlen(data[i]);x++)
			{	
				printf("%c.",data[i][x]);
			
			}
		}
		printf("\n");
	}
	printf("============================================================\n");
}

//=============================================================================
void setHendlerOptions()
{
	//	handler block 
	signal(SIGCHLD,catch_chld);
//	struct sigaction act;
//	act.sa_handler = catch_chld;
//	sigfillset(&act.sa_mask);
//	act.sa_flags = 0; 				//	do every time
//	sigaction(SIGCHLD,&act,NULL);


}

//=============================================================================
void cycle()
{

	char input[MAX_INPUT_LEN];
	int size=0;	
	char **vector_param = NULL;
	int multi_task = 0;
	pid_t child_pid;
	
	//	get input and delete \n symbol on the end of input
	
	
	while(getstring(input,MAX_INPUT_LEN))
	{
	
		if(!strcmp(input,"exit"))
			break;
		
		//	check if have & / remove them / set multi task true
		multi_task = multi_tsk(input);

		//	covert command line to array
		vector_param = commandArr(input,&size);
		
		//	add to array NULL on the end of array
		vector_param = addTostr(vector_param,&size);		
			
		child_pid = fork();
		
		if(fork <0)
			exit(EXIT_FAILURE);
		else if(child_pid == 0)
			exec(vector_param,size);	//	do execvp with vector param
		else if(child_pid > 0)
		{
			
			free_arr(vector_param,size);
			
			if(!multi_task)
				wait4(child_pid,&status, 0,&u_rusage);
			//else//| WUNTRACED ,,WCONTINUED WNOHANG
			//	wait4(child_pid,&status, WNOHANG && WUNTRACED ,&u_rusage);

		}		
	}	

}

//=============================================================================
int main()
{	
	
	setHendlerOptions();
	cycle();
	puts("Bye-Bye");		
	return(EXIT_SUCCESS);
}

