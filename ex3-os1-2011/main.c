#include <stdio.h>
#include <string.h>
#include "shell.h"




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

int main()
{	
	
	setHendlerOptions();
	cycle();
	puts("Bye-Bye");		
	return(EXIT_SUCCESS);
}

