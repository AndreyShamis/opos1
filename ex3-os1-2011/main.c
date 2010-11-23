#include <stdio.h>
#include "mem.h"



#define MAX_INPUT_LEN 80



char **commandArr(const char input[])
{
	char **temp;
	int sit=0;
	int string_start = 0;
	int space_counter=0;
	
	for(sit=0;sit<MAX_INPUT_LEN;sit++)
	{
	
		if(input[sit] == ' ' || input == '\0')
		{
			//temp = alloc_cell(space_counter+1);
			//temp[space_counter] = alloc_string(sit-string_start);
			printf("%d \n",sit-string_start);			
			string_start = sit;

			space_counter++;
		}

	
		if(input == '\0')
			break;
	}
	
	printf("Found : %d .\n", space_counter);
	
	return(temp);
	
}

int main()
{
	
	char input[MAX_INPUT_LEN];
	
	char **po = NULL;
	
	fgets(input,MAX_INPUT_LEN,stdin);
	
	po = commandArr(input);
	
	
	return(EXIT_SUCCESS);
}

