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
//	function which geting input line without \n on the end of string
//	convert the string to array of strings and separate them by space
//	size it is pointer to know which size be the new array of string
//	function retuned new array of strings
char **commandArr(const char input[], int *size)
{
	char 	**temp			=	NULL;	//	temp variable for array
	char 	*new_string		=	NULL;	//	tem variable for string
	char 	**return_temp	=	NULL;	//	variable be returned
	int 	sit				=	0;		//	counter for fro
	int 	string_start 	= 	0;		//	helper variable of start os string
	int 	space_counter	=	0;		//	space counter
	char	prev_char 		= 	'\0';	//	previuos char
	
	for(sit=0;sit<MAX_INPUT_LEN;sit++)
	{
		if((input[sit] == ' ' || input[sit] == '\0') && prev_char != ' ')
		{			
			//	create string
			new_string =substr(input,string_start,sit-string_start);
			
			//	if created string not null
			if(new_string != NULL)
			{
				//	create new array
				temp = alloc_cell(space_counter+1);
		
				//	check if have somthing in array be retuned
				if(return_temp != NULL)
				{
					//	copy from old array to new
					copy_arr(temp,return_temp,space_counter);
					free(return_temp);
				}
			
				//	put new string in new array
				temp[space_counter] = new_string;
				//	increase counter for new string
				string_start = sit+1;	//	set left from space next char
				//	increase space counter
				space_counter++;		//	counter of strings counted
				//	set retuned value to point to temp value
				return_temp = temp;
			}			
		}
		else if(prev_char == ' ' && prev_char == input[sit])
		{	//	if have space after spce
			string_start = sit+1;	
		}
		//	set previous char
		prev_char = input[sit];
		
		//	if and of line exit from for
		if(input[sit] == '\0')		//	if and of string exit from cycle
			break;
	}
	
	//	update pointer of size
	(*size) = space_counter;
	//	return value / return pointer to new array of strings
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
//	function which know to get string
//	function geting pointer to string where this string be puted
//	geting the max size string which can get
//	return true if seccess
//	return false in not
int getstring(char *input,const int max_size)
{
	if(fgets(input,max_size,stdin) != NULL)
	{	
		del_new_line(input);		//	delete \n from string
		return(1);
	}
		
	return(0);
	
}

//=============================================================================
//	function which get input string check if in string we have &
//	if yes delete him from string and return true
//	else return false
int multi_tsk(char *input)
{
    int str_len 	=  	0;			//	helper variable to know string len
    int counter     =	0;			//	counter of charckter
      
    str_len = strlen(input);		//	get len of string
    
    for(counter = str_len;counter>0;counter--)
    {
        if(input[counter] == '&' && input[counter-1] == ' ')
        {                
            input[counter] = ' ';	//	put space in &
            return(1);				//	return true
    	}	
    }
    
    return(0);

}

//=============================================================================
//	fucntion which do execvp with parameters geted in array of string
//	and also get size of this array
//	nithing be returned
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

