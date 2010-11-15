#include <stdio.h>
//======================= DESCRIPTION =========================================
/*
 *	this file give tools to write information to files
 *	he include one function which know to write 
 *	information (type string) from 2-array
 *	by lentgh str_counter(number of strings)
 *	The information be writing into FILE descriptor geted by function
 *	See functions description for more information.
 */
//======================= WRITE TOOLS =========================================
#ifndef WRITE_CES
#define WRITE_SEC

//-------------------- FUNCTION WRITE TO FILE ---------------------------------
//	input 	:	file write descriptor
//				string counter in data structure
//				data structure
void writeFile(FILE *fWrite,const int str_counter,char **dataDB);

#endif
