#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"

#define MAX_STR_LEN  200

#ifndef READ_SEC
#define READ_SEC 
// A function that read text file.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), counter of strings (type
// &char), 
char  **readFile(FILE *fRead,int *str_counter);



// A function that copy tabel of strings.
//-----------------------------------------------------------------------------
// Input: new and old tabels of strings (type dubel pointer).
void copy_arr(char **data_new,char **data_old,const int len);

#endif
