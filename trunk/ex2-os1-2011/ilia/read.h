//======================= DESCRIPTION =========================================
/*
 *	This file give solution for read functions from file
 *	and from console into same string array
 *	(!!! In this version NO READING FROM CONSOLE )
 *	See functions description for more information.
 */
//========================= READ TOOLS ========================================

#include "utils.h"
#include "mem.h"
#include <string.h>

#ifndef READ_SEC
#define READ_SEC 


enum {
	FILE_R 		= 2,		//	can read file from file
	CONSOLE_R 	= 1,		//	cant read from file can read from console
	EOF_R		= 0			//	cant read 

};

// A function that read text file.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), counter of strings (type
// &char), 
char  **readLines(FILE *fRead,int *str_counter);

// A function that copy tabel of strings.
//-----------------------------------------------------------------------------
// 	Input: new and old tabels of strings (type dubel pointer).
//	data_new 	-	new data structure
//	data_old	-	old data structure

void copy_arr(char **data_new,char **data_old,const int len);


//-------------- READ LINE FROM FILE ------------------------------------------
//	input 	pointer to string where be retuned string
//			file descriptor
//	---------------------------------------------------------------------------
//	return	0 - if input == NULL = EOF
//			1 - if input succeful
int readLineFile(char *data,FILE *fRead);


//-------------- READ LINE FROM CONSOLE ---------------------------------------
//	input 	pointer to string where be retuned string
//	---------------------------------------------------------------------------
//	return	0 - if input == NULL = EOF
//			1 - if input succeful
int readLineConsole(char *data);


#endif
