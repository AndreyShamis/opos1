#include <stdio.h>
#include <string.h>
#include "shell.h"

#include "ex1b.h"




int main()
{	
	setHandler();
	setHendlerOptions();
	cycle();
	puts("Bye-Bye");		
	return(EXIT_SUCCESS);
}


void catch_int(int num)
{
	printf("catch_int\n");

}

void catch_stop(int num)
{
	printf("Catch stop\n");
}

void setHandler()
{
	signal(SIGTSTP,catch_stop);
	signal(SIGINT,catch_int);

}
