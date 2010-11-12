#include "write.h"

//-------------------- FUNCTION WRITE TO FILE ---------------------------------
//	input 	:	file write descriptor
//				string counter in data structure
//				data structure
void writeFile(FILE *fWrite,const int str_counter,char **dataDB)
{
	
	int count;			// counter variable
	
	for(count=0;count<str_counter;count++)
		fprintf(fWrite,"%s",dataDB[count]);		//	write line to file

	
}
