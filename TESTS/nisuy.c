#include "stdio.h"
#include "unistd.h"
#include "sys/wait.h"

int main(int argc, char **argv)
{

	char a = 'F';
	
	printf("hi\n");

	int soncounter = 0;
	
	pid_t i = fork();
	

	soncounter++;
	
	if(i < 0)
	{
	
		printf("<0\n");
		printf("%c \n", a);
		a = 'q';
		
		printf("%c \n", a);
	
	}
	
	int id_son = wait(&i);
	printf("Son %d ended. exitstatus = %d\n", id_son, WEXITSTATUS(i));
	
	if(i>0)
	{
		//printf(">0\n");
		//printf("%c -->0\n", a);
		//a = 'D';
		
		//printf("%c --->00\n", a);
		
		i = fork();
		soncounter++;
	
	}
	
	if(i==0)
	{
		printf("------------------------------------------------------\n");
		if(soncounter == 1)		
			execlp("cat" ,"cat","ping.txt",NULL);
		else
			execlp("cat" ,"cat","ping2.txt",NULL);
		
		printf("Me son =0\n");
		printf("soncounter %d\n",soncounter);		
		printf("%s\n",argv[0]);
		printf("%c \n\n", a);
	
	}
	return(0);
}
