#include "shell.h"


//=============================================================================
//	Function which geting string start position and len
//	and return the substring by lentgh and start
char *substr(const char *string, const int start,const int len)
{
	char 	*temp = NULL;				//	pointer to string	
	int 	counter=0;					//	counter for FOR
	int 	len_self=0;					//	helper variable
	int 	string_len = strlen(string);//	helper variable for str len
	
	//	check if needed len is correct
	if(len > string_len || len <0)
		len_self = string_len - start - 1;
	else if (len == 0)		//	if len zero(dont need str)return string NULL
		return((char *)NULL);
	else					//	else set helper variable be len 
		len_self = len;	

	//	create the string space in memory
	temp = alloc_string(len_self+1);
	
	//	copy every char needed to new string
	for(counter = 0 ;counter < len_self;counter++)
		temp[counter] = string[start+counter];
	
	//	put on the end null terminated char
	temp[len_self] = '\0';
	
	//	return the new string
	return(temp);
	
}

//=============================================================================
//	function wich geted array of string and size of him
//	and created new string in this array and puted in the end the NULL
//	which used in execvp
//	return new array of strings with NULL on the end
char **addTostr(char **arr,int *size)
{
	char 	**temp 	= 	NULL;		//	varaiable be returned
	
	temp = alloc_cell((*size)+1); 	//	recreate the array of strings
	copy_arr(temp,arr,*size);		//	copy from old array to new array
	free(arr);						//	free old array
	temp[*size] = (char *) NULL;	//	put on the NULL
	(*size)++;						//	increase counter
	
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
//	function which getting string and delete the \n ion the of string
//	used after fgets which put \n on the and
//	return string without \n in pointer variable
void del_new_line(char *string)
{
	int str_len	=	0;				//	string len variable		
	
	str_len = strlen(string);		//	get line of string
	
						
	if(str_len > 1)					//	if user  not input nothing
		string[str_len-1] = '\0';	//	put null terminated symbol to \n
		
}

//=============================================================================
int getstring(char *input,const int max_size)
{
	if(fgets(input,max_size,stdin) != NULL)
	{	
		del_new_line(input);
		return(1);
	}
		
	return(0);
	
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

