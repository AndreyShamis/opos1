#include "shell.h"




//#############################################################################


//=============================================================================
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

//=============================================================================
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

//=============================================================================
char **commandArr(const char input[], int *size)
{
	char **temp			=	NULL;
	char *new_string	=	NULL;
	char **return_temp	=	NULL;
	int sit=0;
	int string_start = 0;
	int space_counter=0;
	char prev_char = '\0';
	
	for(sit=0;sit<MAX_INPUT_LEN;sit++)
	{
		if((input[sit] == ' ' || input[sit] == '\0') && prev_char != ' ')
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
		else if(prev_char == ' ' && prev_char == input[sit])
		{
			string_start = sit+1;	
		}
	
		prev_char = input[sit];
		
		if(input[sit] == '\0')		//	if and of string exit from cycle
			break;
	}
	
	(*size) = space_counter;
	
	return(return_temp);
	
}

//=============================================================================
void del_new_line(char *string)
{
	int str_len	=	0;			//	string len variable		
	//	get line of string
	str_len = strlen(string);
	//	put null terminated symbol to \n
	
	//	if user  not input nothing
	if(str_len > 1)
		string[str_len-1] = '\0';
		
}

//=============================================================================
int getstring(char *input,const int max_size)
{
	if(fgets(input,max_size,stdin) != NULL)
	{	
		del_new_line(input);
		return(1);
	}
	else
	{
		//input = NULL;
		//printf("Can not read. Pid: %d\n",getpid());
		return(0);
	}	
}

//=============================================================================
int multi_tsk(char *input)
{
    int str_len 	=  	0;
    int counter     =	0;
      
    str_len = strlen(input);
    
    for(counter = str_len;counter>0;counter--)
    {
        if(input[counter] == '&' && input[counter-1] == ' ')
        {                
            input[counter] = ' ';
            return(1);
    	}	
    }
    return(0);

}

//=============================================================================
void exec(char **vector_param,const int size)
{
	int exec_stat = 0;	//	exec status exit parameter

	//	try to do exec with vector param
	exec_stat = execvp(vector_param[0],vector_param); 
	
	//	clean memory
	free_arr(vector_param,size);
	
	//	if execvp fail exit whith exit failure
	if(exec_stat)
	{
		perror("Can not do execvp()\n");
		exit(EXIT_FAILURE);
	}
		
	exit(EXIT_SUCCESS);

}

