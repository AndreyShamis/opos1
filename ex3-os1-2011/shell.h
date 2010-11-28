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
void del_new_line(char *string);

//================== Catch exit Handler =======================================

char **commandArr(const char input[], int *size);

char **addTostr(char **arr,int *size);

char *substr(const char *string, const int start,const int len);

int multi_tsk(char *input);

int getstring(char *input,const int max_size);



void exec(char **vector_param,const int size);


#endif
