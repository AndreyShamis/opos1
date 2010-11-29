#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "ex1b.h"


//=============================================================================
int main()
{	
	setHandler();
	setHendlerOptions();			//	set handler
	cycle();						//	enter to main cycle-function in shell
	puts("Bye-Bye");				//	put bye bye
	return(EXIT_SUCCESS);			//	exit
}
//================== Catch exit Handler =======================================
void catch_chld(pid_t num)
{

	if(WIFEXITED(status))
	{
		wait3(&status,WNOHANG,&u_rusage) ;
		
		long sys_time = u_rusage.ru_stime.tv_sec;
		long sys_timeu =  u_rusage.ru_stime.tv_usec;
		long usr_time = u_rusage.ru_utime.tv_sec;
		long usr_timeu =  u_rusage.ru_utime.tv_usec;
		int exit_stat= status;
		printf("%ld.%06ld ,%ld.%06ld ,%d\
		\n",sys_time,sys_timeu,usr_time,usr_timeu,exit_stat);
	}

}

//=============================================================================
void catch_int(int num)
{
	setHandler();
	printf("\n");			//	print new line for neauty

}

//=============================================================================
void catch_stop(int num)
{
	backgrdnd = 1;
	setHandler();
}

//=============================================================================
void setHandler()
{
	signal(SIGTSTP,catch_stop);
	signal(SIGINT,catch_int);

}

//=============================================================================
void setHendlerOptions()
{
	signal(SIGCHLD,catch_chld);
}

//=============================================================================
void cycle()
{
	char 	input[MAX_INPUT_LEN];			//	variable for input
	int 	size				=	0;		//	size of string array
	char 	**vector_param 		= 	NULL;	//	string array
	int 	multi_task 			= 	0;		//	have multi task process now
	pid_t 	child_pid;						//	child process id
	
	while(getstring(input,MAX_INPUT_LEN))
	{
	
		if(!strcmp(input,"exit"))
			break;
		else if(!strcmp(input,"bg"))
		{
			if(backgrdnd == 1 && stoped_id != 0)
			{
				backgrdnd = 0;
				kill(stoped_id,SIGCONT);
				wait3(&status, WUNTRACED,&u_rusage);
				setHandler();
			}
			
			continue;
			
		}
		//	check if have & / remove them / set multi task true
		multi_task = multi_tsk(input);

		//	covert command line to array
		vector_param = commandArr(input,&size);
		
		//	add to array NULL on the end of array
		vector_param = addTostr(vector_param,&size);		
			
		child_pid = fork();
		
		if(fork <0)
		{
			perror("Can not fork()\n");	//	print error
			exit(EXIT_FAILURE);			//	exit
		}
		else if(child_pid == 0)
			exec(vector_param,size);	//	do execvp with vector param
		else if(child_pid > 0)
		{
			
			free_arr(vector_param,size);
			if(!multi_task)
			{
				if(backgrdnd == 0)
				{
					//backgrdnd = 0;
					stoped_id = child_pid;
					setHandler();
				}
				else
					signal(SIGTSTP,SIG_IGN);
					
				wait3(&status, WUNTRACED,&u_rusage);
				
			}

		}		
	}	

}
//======================= END OF FILE =========================================
