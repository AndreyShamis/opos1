#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#define MAX_INPUT_LEN 30

#ifndef EX5_SEC
#define EX5_SEC

//=============================================================================
//	function which run in cycle while not ^D or user not put exit
//	this function get command from user convert string to array of
//	strings and call to function exec with array of string
void cycle();


//=============================================================================
//	function which getting string and delete the \n ion the of string
//	used after fgets which put \n on the and
//	return string without \n in pointer variable
void del_new_line(char *string);

//=============================================================================
//	function which know to get string
//	function geting pointer to string where this string be puted
//	geting the max size string which can get
//	return true if seccess
//	return false in not
int getstring(char *input,const int max_size);

#endif

