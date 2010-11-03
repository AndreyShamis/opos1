#include "write.h"


void writeFile(FILE *fWrite,const int str_counter,char **dataDB)
{
	
	int i;
	for(i=0;i<str_counter;i++)
	{
		fprintf(fWrite,"%s",dataDB[i]);
		//printf("Yea %s - \n", dataDB[i]);
	}
	
}
