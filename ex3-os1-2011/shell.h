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

struct rusage u_rusage;
int status ;


//=============================================================================
void del_new_line(char *string);

//================== Catch exit Handler =======================================
void catch_chld(pid_t num);

char **commandArr(const char input[], int *size);

char **addTostr(char **arr,int *size);

char *substr(const char *string, const int start,const int len);

int mt(char *input);

int getstring(char *input,const int max_size);

void setHendlerOptions();

void exec(char **vector_param,const int size);

void cycle();



#endif
