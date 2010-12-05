#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "ex4a.h"

//=============================================================================
int main()
{	
	
	setHendlerOptions();			//	set handler
	cycle();						//	enter to main cycle-function in shell
	puts("Bye-Bye");				//	put bye bye
	return(EXIT_SUCCESS);			//	exit
}

//================== Catch exit Handler =======================================
//	handler function to know when child is exited
void catch_chld(pid_t num)
{


	wait3(&status,WNOHANG,&u_rusage) ;

	//	variable help to know times 
	//	like user time and sys time
	long sys_time 	= 	u_rusage.ru_stime.tv_sec;
	long sys_timeu 	=  	u_rusage.ru_stime.tv_usec;
	long usr_time 	= 	u_rusage.ru_utime.tv_sec;
	long usr_timeu 	=  	u_rusage.ru_utime.tv_usec;
	int exit_stat	= 	status;   // exit status
	
	//	print needed information
	printf("%ld.%06ld ,%ld.%06ld ,%d \
	\n",sys_time,sys_timeu,usr_time,usr_timeu,exit_stat);
	
}


//=============================================================================
//	function which seting handler by default
void setHendlerOptions()
{
	signal(SIGTSTP,SIG_IGN);	//	set ignore
	signal(SIGINT,SIG_IGN);		//	set ignore
	signal(SIGCHLD,catch_chld);	//	set handler for sigchld
}

//=============================================================================
//	function which run in cycle while not ^D or user not put exit
//	this function get command from user convert string to array of
//	strings and call to function exec with array of string
void cycle()
{
	char 	input[MAX_INPUT_LEN];			//	variable for input
	int 	size				=	0;		//	size of string array
	char 	**vector_param 		= 	NULL;	//	string array
	int 	multi_task 			= 	0;		//	have multi task process now
	pid_t 	child_pid;						//	child process id
	
	int 	piped_en				=	0;		//	zero if not and some int if yes
	char 	**vector_param2		=	NULL;
	int pipe_d[2];
	
	while(getstring(input,MAX_INPUT_LEN))
	{
	
		if(!strcmp(input,"exit"))
			break;
		else if(!strcmp(input,"\n"))
			continue;

		//	check if have & / remove them / set multi task true
		multi_task = multi_tsk(input);
		
		piped_en = piped(input);

		int cont_p = 0;
			int size1 = 0;
			int size2 = 0;
					
		if(piped_en)
		{
			if(pipe(pipe_d) == -1)
			{
				perror("Can not open pipe \n");
			}
			
			char *input1 = NULL;
			char *input2 = NULL;
			
			
			
			input1 = substr(input,0,piped_en-1);
			input2 = substr(input,piped_en+1,strlen(input)-piped_en);		

			vector_param = commandArr(input1,&size1);
			vector_param2 = commandArr(input2,&size2);
			
			free(input1);
			free(input2);
			child_pid = fork();
			cont_p++;
			child_pid = fork();
		}		
		else
		{
		
			//	covert command line to array
			vector_param = commandArr(input,&size);
			


		
			//	add to array NULL on the end of array
			vector_param = addTostr(vector_param,&size);		
			
			child_pid = fork();
				
		}		

		
		if(fork <0)
		{
			perror("Can not fork()\n");	//	print error
			exit(EXIT_FAILURE);			//	exit
		}
		else if(child_pid == 0)
		{
			if(piped_en && cont_p == 0)
			{
				// first son only to write
				close(pipe_d[0]);
				dup2(STDOUT_FILENO,pipe_d[1]);
				exec(vector_param,size1);	//	do execvp with vector param
				
			}
			else if(piped_en && cont_p == 1)
			{
				//	second son only to read
				close(pipe_d[1]);
				dup2(STDIN_FILENO,pipe_d[0]);
				exec(vector_param2,size2);	//	do execvp with vector param

			}
		
		}
		else if(child_pid > 0)
		{
			
			free_arr(vector_param,size);//	clear memory
			
			if(!multi_task)				//	if not multi task
				wait4(child_pid,&status, 0,&u_rusage);
				
		}		
	}	

}
//======================= END OF FILE =========================================
