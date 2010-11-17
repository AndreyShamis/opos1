//
/*
*
*	Hasimat signalim
*
*
*
*
*/
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

short screen_sever =  0 ;	//	Global variable
	


void do_son()
{

	int i;
	
	
	
	for(i=0;i<5;i++)
	{
		puts("Son \n");
		sleep(2);	
		kill(getpid(),SIGUSR1);
		pause();
	}
}

void do_dad(pid_t son_pid)
{
	int i;
	printf("Me %d", getpid());
	
	for(i=0;i<5;i++)
	{
		pause();
		
		puts("DAD turn\n");
		
		kill(son_pid,SIGUSR1);
		
	
	}
	
}


void f(int s)
{

	;
	//sigprocmask(); //http://opengroup.org/onlinepubs/007908799/xsh/sigprocmask.html
//int sigprocmask(int how, const sigset_t *set, sigset_t *oset);
//int pthread_sigmask(int how, const sigset_t *set, sigset_t *oset);	
}

void catch_int(int sig_num)
{
	printf("\nCATCH INT - Geted sig NUM : %d\n",sig_num);
}

void sig_get(int sig_num)
{
	printf("\n#-#\tSIG GET - Geted sig NUM : \r\t\t\t\t\t\t |%d|\n",sig_num);

	if(sig_num == SIGALRM)
	{
		screen_sever = 1;
		puts("\n It seems you went away \
		lalalalal\n");
		//exit(EXIT_SUCCESS);
		
	}
	
	if(sig_num == 2)
	{
		screen_sever = 0;		
	}

}
int main()
{

	// 0 - screen of
	// 1 = on
	// 2 = user puts ^c
	
/*
           struct sigaction {
               void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
           };
*/
	int i,j;
	struct sigaction act;
	
	//act.sa_handler = catch_int;
	
	act.sa_handler = sig_get;
	sigfillset(&act.sa_mask);
	act.sa_flags = 0; // tamid nahnis 0
	//signal(SIGINT,f);

	sigaction(SIGINT,&act,NULL);

	signal(SIGQUIT,sig_get);
	
	//	когда происходит после аларма 
	//	возвращается на ту строчку на которой было
	//	signal(SIGALRM,sig_get);
	
	//	это продолжает делать после аларма следующую функцию
	sigaction(SIGALRM,&act,NULL);
	

	for(i = 0; i< 0;i++)
	{
		screen_sever = 0;
		printf("Cicle %d\n",i);
		alarm(2);
		getchar();
		alarm(0);		
	
		while(screen_sever == 1)
		{
			printf("Screen sever == 1\n");
			sleep(1);
		}
		if(screen_sever == 0)
		{
			for(j=0;j<10;j++)
			{
				;
			}
		}
	}
	
	signal(SIGUSR1,sig_get);
	pid_t ii = fork();
	
	if(ii<0)
		printf("NE RABOTAET\n");
 	else if(!ii)
		do_son();
	else if(ii)
		do_dad(ii);
		
	return(0);

}



