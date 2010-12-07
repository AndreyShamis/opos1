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
void catch_chld(int num)
{

	struct rusage u_rusage;		//	struct used for get times
	int status ;				//	to know which status was exited
	getrusage(RUSAGE_CHILDREN,&u_rusage);

	int a = wait3(&status,WUNTRACED || WNOHANG,&u_rusage) ;

	//	variable help to know times 
	//	like user time and sys time
	long sys_time 	= 	u_rusage.ru_stime.tv_sec;
	long sys_timeu 	=  	u_rusage.ru_stime.tv_usec;
	long usr_time 	= 	u_rusage.ru_utime.tv_sec;
	long usr_timeu 	=  	u_rusage.ru_utime.tv_usec;
	int exit_stat	= 	status;   // exit status
	
	//	print needed information
	printf("%ld.%06ld ,%ld.%06ld ,%d \
	 a:%d\n",sys_time,sys_timeu,usr_time,usr_timeu,exit_stat,a);
	
}

void catch_chld2(int num,siginfo_t *sig_i,void *ucont)
{

//	struct rusage rsg;		//	struct used for get times
//	int status ;				//	to know which status was exited
	//getrusage(RUSAGE_CHILDREN,&rsg);
//	printf("PID: %d\n",sig_i->si_pid);
//	int a = wait3(&status,WNOHANG ||WUNTRACED,&rsg);
//	if(a < 0)
//	{
		waitpid(-1,0,WNOHANG);

//		wait4(sig_i->si_pid,&status,WNOHANG || WUNTRACED,&rsg);
//	}
	//int a = wait3(&status,WUNTRACED || WNOHANG,&u_rusage) ;

	//	variable help to know times 
	//	like user time and sys time
	//long sys_time 	= 	u_rusage.ru_stime.tv_sec;
	//long sys_timeu 	=  	u_rusage.ru_stime.tv_usec;
	//long usr_time 	= 	u_rusage.ru_utime.tv_sec;
	//long usr_timeu 	=  	u_rusage.ru_utime.tv_usec;

//	printf("A: %d\n",a);
//	printf("%ld.%06ld ,%ld.%06ld ,%d\n",rsg.ru_stime.tv_sec, rsg.ru_stime.tv_usec,rsg.ru_utime.tv_sec,rsg.ru_utime.tv_usec ,status);

	printf("%ld ,%ld ,%d\n",sig_i->si_stime,sig_i->si_utime,sig_i->si_status);
}


//=============================================================================
//	function which seting handler by default
void setHendlerOptions()
{
	signal(SIGTSTP,SIG_IGN);	//	set ignore
	signal(SIGINT,SIG_IGN);		//	set ignore
	struct sigaction act;
	
	//act.sa_handler = catch_chld;
	act.sa_sigaction = catch_chld2;
	act.sa_flags =  SA_RESTART | SA_SIGINFO;
	sigfillset(&act.sa_mask);
	sigaction(SIGCHLD,&act,NULL);
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

	int 	piped_en				=	0;	//	zero if not and some int if yes
	int 	pipe_d[2];
	int 	cont_p 					= 	0;	//	couner for fork
	int 	fork_size				=	0;	//	fork size 

	while(getstring(input,MAX_INPUT_LEN))
	{
	
		if(!strcmp(input,"exit"))		//	exit from program
			break;
		else if(!strcmp(input,"\n"))	//	ignore enter
			continue;

		//	check if have & / remove them / set multi task true
		multi_task = multi_tsk(input);
	
		piped_en = piped(input);		//	check if it is piped command
		
		//	open pipe if found pipe symbol in input
		if(piped_en && pipe(pipe_d) == -1)
			PipeError();
		
		//	get fork size be created
		fork_size = preformForkSize(piped_en);
	
		for(cont_p=0;cont_p<fork_size;cont_p++)
		{
		
			//	convert the string to array of string	
			arrv = PipeSeparation(arrv,piped_en, cont_p,&size,input);
			
			child_pid = fork();				//	fork
				
			checkForkStatus(child_pid);		//	check if fork success
								
			if(child_pid == 0)
			{
				PreProc_Creation(piped_en,cont_p,pipe_d);
				exec(arrv,size);	//	do execvp with vector param
			}
			else if(child_pid > 0)
			{
				free_arr(arrv,size);//	clear memory
			
				if(!multi_task && !piped_en)		//	if not multi task
					wait(&child_pid);
				//	wait4(child_pid,&status, WUNTRACED,&u_rusage);
				//else if(multi_task)
				//	wait4(child_pid,&status, WNOHANG,&u_rusage);	

			}	

		}
		
		close_pipe(pipe_d,piped_en);			//	close pipe if the open

	}
}
//======================= END OF FILE =========================================
