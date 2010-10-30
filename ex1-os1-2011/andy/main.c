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
void copy_arr(char **data_new,char **data_old,int len);
char **alloc_cell(int size);





void sort_by_id();

char **alloc_cell(int size)
{
    char **new_cell = NULL;      // create new pointer-pointer

    new_cell = (char**)malloc(sizeof(char*)*size) ;   // alloc memory

    if(new_cell == NULL)        // check if have memory
    	printf("Error ----- all\n");
    
    return(new_cell);
}

void copy_arr(char **data_new,char **data_old,int len)
{
	int i;
	//printf("Start:\n");
	for(i=0;i<len;i++)
	{
		//printf("S %d :\t", i);
		data_new[i] = data_old[i];
	
	}
	//printf("END:\n");
}

void free_arr(char **data, int len)
{
	int i;
	
	for(i=0;i<len;i++)
	{
		free(data[i]);
	
	}
}

void print_arr(char **data, int size)
{
	int i;
	
	for(i=0;i<size;i++)
	{
		//for(x=0;x<strlen(data[i]);x++)
			printf("%s.",data[i]);
			
		printf("\n");
	}
}

int getID(char *str);
int cmpName(char *name1,char *name2);

void sort_by_name(char **data,int size)
{
	int i, x;
	
	char *temp;
	for(i=0;i<size;i++)
	{
		for(x=0;x<size;x++)
		{
			if(cmpName(data[i],data[x]) ==1)
			{
				//printf("hz 1\n");
				temp = data[x];
				data[x]=data[i];
				data[i]=temp;
				//break;
			}			
		}
	}

}



//--------------  Prototypes section ------------------------------------------

//------------------------- Main section --------------------------------------
int main(int argc, char *argv[])
{
	
	char key[5];		//	Variable for menu		// TODO
	//char buf[20];		//	Variable for In data	// TODO
	
	char data[100];
	
	char **datap=NULL;
	
	FILE *fRead;		//	Var for red file
	FILE *fWrite;		// 	Var for write file
		
	int ind=0;
	
	//int res;
	
	//res = strcmp("a","ac");
	//printf("%d",res);
	//res = strcmp("acb","ac");
	//printf("%d",res);
	if(argc == 3 )
	{

		fRead = fopen(argv[1],"r");
		fWrite = fopen(argv[2],"w");
	
		if(fRead == NULL)
			printf("Can`t read file %s \n", argv[1]);
		else
			while(fgets(data,50,fRead) != NULL)	// TODO CONST
			{
			
				char **temp=NULL;
				//printf("1:\n");
				char *str = (char*)malloc( (sizeof(char)*strlen(data) +1 ));
				//printf("2:\n");
				temp = alloc_cell(ind+1);
				//printf("3:\n");
				copy_arr(temp,datap,ind);
				//printf("4:\n");
				//free_arr(datap,ind);
				free(datap);
				datap = temp;
				
				
				strcpy(str,data);				
				temp[ind] = str;
				

				//printf("%s \n",temp[ind]);	
				
				ind++;
				
			}
		
		
		fgets(key,5,stdin);			// TODO Const
		print_arr(datap,ind);
		printf("\n\n");
		
		if(!strcmp(key,"name"))
			sort_by_name(datap,ind);
		else if(!strcmp(key,"id"))
			sort_by_id();
	
		print_arr(datap,ind);
		printf("DATA %s \n", argv[1]);
		//return ;
	
		fclose(fRead);			// close readed file
		fclose(fWrite);			// close writed file
	
	}
	
	free_arr(datap,ind);
	free(datap);
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
	int len;
	

	char name1_str[strlen(name1)];
	memset(name1_str,'0',strlen(name1));
	
	char name2_str[strlen(name2)];
	memset(name2_str,'0',strlen(name2));
	
	len = strlen(name1);
	for(count=0;count<len;count++)
	{
		if(name1[count] == ' ')
		{
			strncpy(name1_str,name1,count);
			name1_str[count] = '\0';
			break;
		}
			
	}
	
	len = strlen(name2);
	for(count=0;count<len;count++)
	{
		if(name2[count] == ' ')
		{
			strncpy(name2_str,name2,count);
			name2_str[count] = '\0';
			break;
		}
			
	}
	
	if(strcmp(name1_str,name2_str)<0)
		return(1);


	return(0);

	
}

