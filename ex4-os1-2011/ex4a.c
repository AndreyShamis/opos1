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
	
	
	//========================	NEW BLOCK =========================
	int 	piped_en				=	0;	//	zero if not and some int if yes
	int 	pipe_d[2];
	int 	cont_p 					= 	0;
	//========================	NEW BLOCK =========================

	while(getstring(input,MAX_INPUT_LEN))
	{
	
		if(!strcmp(input,"exit"))		//	exit from program
			break;
		else if(!strcmp(input,"\n"))	//	ignore enter
			continue;

		//	check if have & / remove them / set multi task true
		multi_task = multi_tsk(input);

	//========================	NEW BLOCK =========================		
		piped_en = piped(input);		//	check if it is piped command
		
		if(piped_en && pipe(pipe_d) == -1)
		{
				perror("Can not open pipe \n");
				exit(EXIT_FAILURE);
		}	
			
		int fork_size = 0;
		
		if(piped_en)
			fork_size = 2;
		else
			fork_size = 1;
		
		for(cont_p=0;cont_p<fork_size;cont_p++)
		{
			if(piped_en)
			{
				char *input_h =	NULL;
				
				if(cont_p == 0)
					input_h=substr(input,0,piped_en-1);
				else
					input_h=substr(input,piped_en+2,strlen(input)-piped_en-2);
				
				//	covert command line to array
				vector_param = commandArr(input_h,&size);
				//	free input_h variable
				free(input_h);
				
			}
	//========================	NEW BLOCK =========================
			else
				vector_param = commandArr(input,&size);
			
			//	add to array NULL on the end of array
			vector_param = addTostr(vector_param,&size);		
			
			child_pid = fork();
				
			checkForkStatus(child_pid);
								
			if(child_pid == 0)
			{
				if(piped_en && cont_p == 0)
					Proc_write(pipe_d);
				else if(piped_en && cont_p == 1)
					Proc_read(pipe_d);
				
				exec(vector_param,size);	//	do execvp with vector param
			}
			else if(child_pid > 0)
			{
				free_arr(vector_param,size);//	clear memory
			
				if(!multi_task &&!piped_en)				//	if not multi task
					wait4(child_pid,&status, WUNTRACED,&u_rusage);
		//	HUY ZNAET----->		//wait4(child_pid,&status, WUNTRACED|| WNOHANG,&u_rusage);
			//	else if(piped_en)
		//			waitpid(child_pid, &status, WUNTRACED || WNOHANG );			
			}	

		}
		if(piped_en)
			close_pipe(pipe_d);

	}
}
//======================= END OF FILE =========================================
