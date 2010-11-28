#include "shell.h"




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

//================== Catch exit Handler =======================================
void catch_chld(pid_t num)
{


	while(wait4(-1,&status,WNOHANG,&u_rusage) > 0)
	{
		;
		//getrusage(num,&u_rusage);
		//printf("lol\n Status:%d\n Num %d\n",status,num);
	}
	long sys_time = u_rusage.ru_stime.tv_sec;
	long sys_timeu =  u_rusage.ru_stime.tv_usec;
	long usr_time = u_rusage.ru_utime.tv_sec;
	long usr_timeu =  u_rusage.ru_utime.tv_usec;
	int exit_stat= status;
	printf("%ld.%06ld ,%ld.%06ld ,%d\n",sys_time,sys_timeu,usr_time,usr_timeu,exit_stat);
	
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
		printf("Can not read. Pid: %d\n",getpid());
		return(0);
	}	
}

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

void setHendlerOptions()
{
	//	handler block 
	signal(SIGCHLD,catch_chld);
//	struct sigaction act;
//	act.sa_handler = catch_chld;
//	sigfillset(&act.sa_mask);
//	act.sa_flags = 0; 				//	do every time
//	sigaction(SIGCHLD,&act,NULL);


}

void cycle()
{

	char input[MAX_INPUT_LEN];
	int size=0;	
	char **vector_param = NULL;
	int multi_task = 0;
	pid_t child_pid;
	
	//	get input and delete \n symbol on the end of input
	
	
	while(getstring(input,MAX_INPUT_LEN))
	{
	
		if(!strcmp(input,"exit"))
			break;
		
		//	check if have / remove them / set multi task true
		multi_task = multi_tsk(input);

		//	covert command line to array
		vector_param = commandArr(input,&size);
		
		//	add to array NULL on end of array
		vector_param = addTostr(vector_param,&size);		
			
		child_pid = fork();
		
		if(fork <0)
			exit(EXIT_FAILURE);
		else if(child_pid == 0)
			exec(vector_param,size);	//	do execvp with vector param
		else if(child_pid > 0)
		{
			
			free_arr(vector_param,size);
			
			if(!multi_task)
				wait4(child_pid,&status, 0,&u_rusage);
			//else//| WUNTRACED ,,WCONTINUED WNOHANG
			//	wait4(child_pid,&status, WNOHANG && WUNTRACED ,&u_rusage);

		}		
	}	

}

