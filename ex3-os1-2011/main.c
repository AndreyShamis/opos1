#include <stdio.h>
#include <string.h>
#include "mem.h"



#define MAX_INPUT_LEN 80

void print_arr_t(char **data,const int size)
{
	int i=0,x=0;


		//printf("%d \n",strlen(data[i]));
	
	for(i=0;i<size;i++)
	{

		for(x=0;x<strlen(data[i]);x++)
		{	
			if(data[i][x] == ' ')
				printf("\r\t\t\t\t");
				
			printf("%c",data[i][x]);
			
		}
		printf("\n");
	}
	printf("============================================================\n");
}
//#############################################################################



char *substr(const char *string, const int start,const int len)
{
	char *temp = NULL;
	int counter=0;
	int len_self=0;
	int string_len = strlen(string); 
	
	if(len > string_len || len <0)
		len_self = string_len - start - 1;
	else
		len_self = len;

	printf("Start: %d , Len: %d , SELF LEN: %d\n",start,len,len_self);
		
	temp = alloc_string(len_self+1);
	
	for(counter = 0 ;counter < len_self;counter++)
		temp[counter] = string[start+counter];
	
	temp[len_self] = '\0';
	
	return(temp);
	
}


char **commandArr(const char input[], int *size)
{
	char **temp			=	NULL;
	char *new_string	=	NULL;
	char **return_temp	=	NULL;
	int sit=0;
	int string_start = 0;
	int space_counter=0;
	
	for(sit=0;sit<MAX_INPUT_LEN;sit++)
	{
	
		if((input[sit] == ' ' || input[sit] == '\0'))
		{
			
			temp = alloc_cell(space_counter+1);
			//printf("%s \n",substr(input,string_start,sit-string_start));
			
			new_string =substr(input,string_start,sit-string_start);
			
			if(return_temp != NULL)
			{
				copy_arr(temp,return_temp,space_counter);
				free(return_temp);
			}
			
			temp[space_counter] = new_string;
			

			string_start = sit+1;	//	set left from space next char

			space_counter++;		//	counter of strings counted
			
			return_temp = temp;
		}

	
		if(input[sit] == '\0')		//	if and of string exit from cycle
			break;
	}
	
	printf("Found : %d .\n", space_counter);
	
	(*size) = space_counter;
	
	return(return_temp);
	
}

int main()
{
	
	char input[MAX_INPUT_LEN];
	int size=0;	
	char **vector_param = NULL;
	
	fgets(input,MAX_INPUT_LEN,stdin);
	
	vector_param = commandArr(input,&size);
	
	print_arr_t(vector_param,size);
	
	
	free_arr(vector_param,size);
		
	return(EXIT_SUCCESS);
}

