#include "read.h"

// A function that read text file.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), counter of strings (type
// &char), 
char **readFile(FILE *fRead,int *str_counter)
{
	char **temp=NULL, **dataDB=NULL;
	char data[MAX_STR_LEN];
	char *str=NULL;

	while(fgets(data,MAX_STR_LEN,fRead) != NULL)	// TODO CONST
	{
		str = (char*)malloc( (sizeof(char)*strlen(data))+1);

		
		temp = alloc_cell((*str_counter)+1);
		
		copy_arr(temp,dataDB,*str_counter);
		free(dataDB);
		dataDB = temp;
		temp = NULL;
		strcpy(str,data);
		dataDB[(*str_counter)] = str;

		(*str_counter)++;
	}
	
	return(dataDB);
}


// A function that copy tabel of strings.
//-----------------------------------------------------------------------------
// Input: new and old tabels of strings (type dubel pointer).
void copy_arr(char **data_new,char **data_old,const int len)
{
	int i;

	for(i=0;i<len;i++)
		data_new[i] = data_old[i];
}
