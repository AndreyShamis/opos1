#include <stdio.h>

#ifndef WRITE_CES
#define WRITE_SEC

//-------------------- FUNCTION WRITE TO FILE ---------------------------------
//	input 	:	file write descriptor
//				string counter in data structure
//				data structure
void writeFile(FILE *fWrite,const int str_counter,char **dataDB);

#endif
