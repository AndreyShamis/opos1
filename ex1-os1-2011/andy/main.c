/*
 * EX1 :: 
 * =============================================================
 * Writen by: Andrey Shamis, id: 321470882, login:andreysh
 *
 *  
 *  
 */

//------------------------- including section ---------------------------------
#include <stdio.h>

//const int MAX_STR_LEN 5;

void sort_by_name()
{
	printf("By name\n");

}


void sort_by_id()
{
	printf("By id\n");

}

//------------------------- Main section --------------------------------------
int main(int arvc, char *argv[])
{
	
	char key[5];		//	Variable for menu
	char buf[20];		//	Variable for In data
	
	FILE *fRead;
	FILE *fWrite
	
	fRead = fopen(argv[1],"r");
	fWrite = fopen(argv[2],"w");
	
	if(fRead == NULL)
		printf("Can`t read file %s \n", argv[1]);
	else
		while(fgets(buf,20,fRead) != NULL)
			printf("%s \n",buf);	
	
	gets(key);
	
	if(!strcmp(key,"name"))
		sort_by_name();
	else if(!strcmp(key,"id"))
		sort_by_id();
	
	printf("DATA %s \n", argv[1]);
	//return ;
	
	fclose(fRead);			// close readed file
	fclose(fWrite);			// close writed file

	return(1);
}
