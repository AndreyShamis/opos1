#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <errno.h>
#include <signal.h>
#include <sys/resource.h>	//	for russage
#include "mem.h"

#define MAX_INPUT_LEN 30

#ifndef SHELL_SEC
#define SHELL_SEC


//=============================================================================
//	function which getting string and delete the \n ion the of string
//	used after fgets which put \n on the and
//	return string without \n in pointer variable
void del_new_line(char *string);

//================== Catch exit Handler =======================================

char **commandArr(const char input[], int *size);

//=============================================================================
//	function wich geted array of string and size of him
//	and created new string in this array and puted in the end the NULL
//	which used in execvp
//	return new array of strings with NULL on the end
char **addTostr(char **arr,int *size);

//=============================================================================
//	Function which geting string start position and len
//	and return the substring by lentgh and start
char *substr(const char *string, const int start,const int len);

int multi_tsk(char *input);

int getstring(char *input,const int max_size);



void exec(char **vector_param,const int size);


#endif
