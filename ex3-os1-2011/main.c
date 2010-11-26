#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "mem.h"



#define MAX_INPUT_LEN 30





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
//#############################################################################



char *substr(const char *string, const int start,const int len)
{
	char *temp = NULL;
	int counter=0;
	int len_self=0;
	int string_len = strlen(string); 
	
	if(len > string_len || len <0)
		len_self = string_len - start - 1;
	else if (len == 0)
		return(NULL);
	else
		len_self = len;

	//printf("Start: %d , Len: %d , SELF LEN: %d; Used: %d\n",start,len,len_self,len_self+1);
		
	temp = alloc_string(len_self+1);
	
	for(counter = 0 ;counter < len_self;counter++)
		temp[counter] = string[start+counter];
	
	temp[len_self] = '\0';
	
	return(temp);
	
}


char **addTostr(char **arr,int *size)
{
	char 	**temp = NULL;
	
	temp = alloc_cell((*size)+1);
	copy_arr(temp,arr,*size);
	free(arr);
	temp[*size] = (char *) NULL;
	(*size)++;
	
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
		if(input[sit] == ' ' || input[sit] == '\0')
		{			
			new_string =substr(input,string_start,sit-string_start);
			
			if(new_string != NULL)
			{
			
				temp = alloc_cell(space_counter+1);
		
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
			
		}

	
		if(input[sit] == '\0')		//	if and of string exit from cycle
			break;
	}
	
	//printf("Found : %d .\n", space_counter);
	
	(*size) = space_counter;
	
	return(return_temp);
	
}

int multiTask(char **data, const int size)
{
	int counter=0;
	
	for(counter = 0;counter < size;counter++)
		if(strlen(data[counter]) == 1 && data[counter][0] == '&')
		{
			data[counter][0] = ' ';
			return(1);
		}
		
	return(0);
	
}

void catch_chld(const int num)
{
	int sys_time = 0;
	int usr_time = 0;
	int exit_stat= 0;
	printf("CHILD NUMBER:%d\t",num);
	
	printf("ppid %d\t", getppid());
	printf("pid %d\n", getpid());
	
	printf("%d ,%d ,%d\n",sys_time,usr_time,exit_stat);
}

void del_new_line(char *string)
{
	int str_len	=	0;			//	string len variable		
	//	get line of string
	str_len = strlen(string);
	//	put null terminated symbol to \n
	
	if(str_len > 0)
		string[str_len-1] = '\0';
		
}


void getstring(char *input,const int max_size)
{
	if(fgets(input,max_size,stdin) != NULL)
		del_new_line(input);
	else
		input = NULL;	
}

void exec(char **vector_param,const int size)
{
	int exec_stat = 0;
	
	exec_stat = execvp(vector_param[0],vector_param); 

	free_arr(vector_param,size);
		
	if(exec_stat)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);

}

void setHendlerOptions()
{
	//	handler block 
	struct sigaction act;
	act.sa_handler = catch_chld;
	sigfillset(&act.sa_mask);
	act.sa_flags = 0; 				//	do every time
	sigaction(SIGCHLD,&act,NULL);


}

int main()
{	
	char input[MAX_INPUT_LEN];
	int size=0;	
	char **vector_param = NULL;
	int multi_task = 0;
	pid_t status ;
	
	
	getstring(input,MAX_INPUT_LEN);
	
	while(input != NULL)
	{
	
		if(!strcmp(input,"exit"))
			break;
		else if(!strcmp(input,""))
		{
			getstring(input,MAX_INPUT_LEN);
			continue;
		
		}
		//	covert command line to array
		vector_param = commandArr(input,&size);
		
		//	check if have & in array/ remove them
		multi_task = multiTask(vector_param,size);
		//	add to array NULL on end of array
		vector_param = addTostr(vector_param,&size);		
		
		
		status = fork();

		
		if(fork <0)
			exit(EXIT_FAILURE);
		else if(status == 0)
			exec(vector_param,size);
		else if(status > 0)
		{
			if(multi_task)
				printf("\nEnter to MULTI TASK MODE\n");
			else
				wait4(&status);
			free_arr(vector_param,size);
		}
		
		getstring(input,MAX_INPUT_LEN);
				
	}	

	puts("Bye-Bye");		
	return(EXIT_SUCCESS);
}

