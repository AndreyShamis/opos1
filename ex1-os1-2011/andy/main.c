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
#include <stdlib.h>
#include <string.h>

//-------------------------  Const section ------------------------------------
//const int MAX_STR_LEN 5;

//------------------------------ Sort By NAME ---------------------------------
void sort_by_name(char **data)
{
	int high;
	
	high = sizeof(data);
	printf("size: %d \n",high);
	printf("By name\n");

}




void sort_by_id();

int getID(char *str);
int cmpName(char *name1,char *name2);
//--------------  Prototypes section ------------------------------------------

//------------------------- Main section --------------------------------------
int main(int argc, char *argv[])
{
	
	char key[5];		//	Variable for menu		// TODO
	//char buf[20];		//	Variable for In data	// TODO
	
	char data[10][20];
	
	FILE *fRead;		//	Var for red file
	FILE *fWrite;		// 	Var for write file
		
	int ind=0;
	
	if(argc == 3 )
	{

		fRead = fopen(argv[1],"r");
		fWrite = fopen(argv[2],"w");
	
		if(fRead == NULL)
			printf("Can`t read file %s \n", argv[1]);
		else
			while(fgets(data[ind],20,fRead) != NULL)	// TODO CONST
			{
			
				//fputs(buf,data[ind]);
				printf("%s \n",data[ind]);	
				
				//printf("---- %d \n",getID(data[ind]));
				
				ind++;
			}
		
		
		fgets(key,4,stdin);			// TODO Const
	
		if(!strcmp(key,"name"))
			sort_by_name(data);
		else if(!strcmp(key,"id"))
			sort_by_id();
	
		printf("DATA %s \n", argv[1]);
		//return ;
	
		fclose(fRead);			// close readed file
		fclose(fWrite);			// close writed file
	
	}
	

	return(1);
}

//------------------------------ Sort By ID -----------------------------------
void sort_by_id()
{
	printf("By id\n");

}

int getID(char *str)
{
	int count;
	char id[strlen(str)];
	int result;
	
	for(count=0;count<strlen(str);count++)
	{
		if(str[count] == ' ')
		{
			strncpy(id,str,count+1);
			break;
		}
			
	}
	
	result= atoi(id);

	printf("%d \n",result);

	return(result);
}

int cmpName(char *name1,char *name2)
{
	int count;
	
	int name1_len;
	int name2_len;
	
	char name1_str[strlen(name1)];
	char name2_str[strlen(name2)];
	
	for(count=0;count<strlen(name1);count++)
	{
		if(name1_str[count] == ' ')
		{
			//strncpy(id,str,count+1);
			
			name1_len = count-1;
			strncpy(name1_str,name1,count-1);

			break;
		}
			
	}
	
	
	for(count=0;count<strlen(name2);count++)
	{
		if(name2_str[count] == ' ')
		{
			//strncpy(id,str,count+1);
			strncpy(name1_str,name1,count-1);
			
			name2_len = count-1;
			break;
		}
			
	}
	
	if(strcmp(name1_str,name2_str))
	{
		printf("%s \n",name1_str);
		printf("%s \n",name2_str);
		return(1);
	}
	else
	{
		printf("%s \n",name2_str);
		printf("%s \n",name1_str);
		return(0);
	}

	
}

