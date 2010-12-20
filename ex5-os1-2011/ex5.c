#include "ex5.h"


//=============================================================================
int main()
{
	cycle();						//	enter to main cycle-function in shell
	puts("Bye-Bye");				//	put bye bye
	return(EXIT_SUCCESS);			//	exit
}


//=============================================================================
//	function which run in cycle while not ^D or user not put exit
//	this function get command from user convert string to array of
//	strings and call to function exec with array of string
void cycle()
{
	char 	input[MAX_INPUT_LEN];		//	variable for input
	FILE 	*pipe_fp;					//	Var for popen.

	while(getstring(input,MAX_INPUT_LEN))
	{

		if(!strcmp(input,"exit"))		//	exit from program
			break;
		else if(!strcmp(input,"\n"))	//	ignore enter
			continue;

		if((pipe_fp = popen(input,"w")) == NULL)
		{
			perror("popen _error");	//	print error
			exit(EXIT_FAILURE);			//	exit
		}
		else
			pclose(pipe_fp);
			
	}
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

//======================= END OF FILE =========================================
