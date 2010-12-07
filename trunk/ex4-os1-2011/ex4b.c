#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "ex4b.h"


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
//	handler function to know when child is exited
void catch_chld(pid_t num)
{
	setHendlerOptions();				//	reset handler
	
	wait3(&status,WNOHANG,&u_rusage);	//	waiting for data

	if(!WEXITSTATUS(status) && !WIFSTOPPED(status) && status>-1) 
	{
		
	
		//	variable help to know times 
		//	like user time and sys time
		long sys_time 	= 	u_rusage.ru_stime.tv_sec;
		long sys_timeu 	=  	u_rusage.ru_stime.tv_usec;
		long usr_time 	= 	u_rusage.ru_utime.tv_sec;
		long usr_timeu 	=  	u_rusage.ru_utime.tv_usec;
		int exit_stat	= 	status;   // exit status

		status = -1;					//	to know if it is exited
		//	print needed information	
		printf("%ld.%06ld ,%ld.%06ld ,%d \
		\n",sys_time,sys_timeu,usr_time,usr_timeu,exit_stat);		
	
	}

}

//=============================================================================
//	handler for SIGINT
void catch_int(int num)
{
	setHandler();
	printf("\n");			//	print new line for neauty

}

//=============================================================================
//	handler for SIGTSTP
void catch_stop(int num)
{
	backgrdnd = 1;
	setHandler();
}

//=============================================================================
//	function which seting handler by default
void setHandler()
{
	signal(SIGTSTP,catch_stop);
	signal(SIGINT,catch_int);

}

//=============================================================================
//	function which seting handler by default but only for SIGCHLD
void setHendlerOptions()
{
	signal(SIGCHLD,catch_chld);
}

//=============================================================================
//	function which run in cycle while not ^D or user not put exit
//	this function get command from user convert string to array of
//	strings and call to function exec with array of string
void cycle()
{
	char 	input[MAX_INPUT_LEN];			//	variable for input
	int 	size				=	0;		//	size of string array
	char 	**arrv 				= 	NULL;	//	string array
	int 	multi_task 			= 	0;		//	have multi task process now
	pid_t 	child_pid;						//	child process id
	
	//========================	NEW BLOCK =========================
	int 	piped_en				=	0;	//	zero if not and some int if yes
	int 	pipe_d[2];
	int 	cont_p 					= 	0;	//	couner for fork
	int 	fork_size				=	0;	//	fork size 
	
	status = 0;
	while(getstring(input,MAX_INPUT_LEN))
	{
		
		if(!strcmp(input,"exit"))
			break;							//	exit from while
		else if(!strcmp(input,"\n"))
			continue;
		else if(!strcmp(input,"bg"))		//	check if user send "bg"
		{
			//	check if have some body in background and him pid not 0
			if(backgrdnd == 1 && stoped_id != 0)
			{
				backgrdnd = 0;				//	reset to know if can put some
											//	to background
				kill(stoped_id,SIGCONT);	//	send signal to continue
				wait3(&status, WUNTRACED,&u_rusage);	//	wait him
				//setHandler();				//	reset handler by default
			}

			continue;						//	contunue by while
			
		}
		//	check if have & / remove them / set multi task true
		multi_task = multi_tsk(input);
	
		piped_en = piped(input);		//	check if it is piped command
		
		if(piped_en && pipe(pipe_d) == -1)
			PipeError();
		
		//	get fork size be created
		fork_size = preformForkSize(piped_en);
		
		for(cont_p=0;cont_p<fork_size;cont_p++)
		{
			//	convert the string to array of string	
			arrv = PipeSeparation(arrv,piped_en, cont_p,&size,input);
			
			child_pid = fork();					//	do fork
				
			checkForkStatus(child_pid);			//	check if fork success
								
			if(child_pid == 0)
			{
				PreProc_Creation(piped_en,cont_p,pipe_d);
				
				status = 0;
				if(multi_task)
				{
					//	if son run whith & set ignore signal
					signal(SIGTSTP,SIG_IGN);	//	can not send SIGTSTP
					signal(SIGINT,SIG_IGN);		//	can not send SIGINT		
			
				}
				
				exec(arrv,size);	//	do execvp with vector param
			}
			else if(child_pid > 0)
			{
			
				free_arr(arrv,size);
				
				if(!multi_task && !piped_en)//	if not multi task process
				{
			
					if(backgrdnd == 0 )		//	check if dont have process
											//	in background
						stoped_id = child_pid;	//	set global pid
		
					wait3(&status, WUNTRACED,&u_rusage);
				
				}
				else
					status = 0;				//	to give options to print
											//	exit time for process which was
											//	run whith &			
			}		

		}
		
		
		close_pipe(pipe_d,piped_en);			//	close pipe if the open
	}

}
//======================= END OF FILE =========================================