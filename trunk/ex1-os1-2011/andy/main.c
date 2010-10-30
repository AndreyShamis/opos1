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
#include <ctype.h>

//-------------------------  Const section ------------------------------------
//const int MAX_STR_LEN 5;

//------------------------------ Sort By NAME ---------------------------------
void copy_arr(char **data_new,char **data_old,int len);
char **alloc_cell(int size);
int popID(const char *str,const int start);
int getID(const char *str);
void sort_by_id(char **data,int size);
int find_space(const char *str);





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


int cmpName(const char *name1,const char *name2);

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
		
		
		fgets(key,3,stdin);			// TODO Const
		
		print_arr(datap,ind);
		printf("\n\n");
		
		if(!strcmp(key,"name"))
			sort_by_name(datap,ind);
		else if(!strcmp(key,"id"))
			sort_by_id(datap,ind);
	
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
void sort_by_id(char **data,int size)
{
	int i,x;
	
	char *temp;
	for(i=0;i<size;i++)
	{
		//printf("Debuf: %s\n",data[i]);
		getID(data[i]);
		for(x=0;x<size;x++)
		{
			if(getID(data[i])<getID(data[x]))
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

int getID(const char *str)
{
	int count;
	//char id[strlen(str)];
	int result;
	
	for(count=0;count<strlen(str);count++)
	{
		if(str[count] == ' ')
		{
			//printf("start ");
			result = popID(str,count+1);
			//printf("%d\n\n",result);
			break;
		}
			
	}

	return(result);
}


int popID(const char *str,const int start)
{
	int count,i=0;
	char temp[strlen(str)];
	
	for(count=start;count<strlen(str);count++)
	{
		if(isdigit(str[count]))
		{
			temp[i]=str[count];
			i++;
		}
		else
		{
			temp[i] = '\0';
			break;
			
		}
	}
	
	return(atoi(temp));
	
}

int cmpName(const char *name1,const char *name2)
{
	
	int count;

	char name1_str[strlen(name1)];
	memset(name1_str,'0',strlen(name1));
	
	char name2_str[strlen(name2)];
	memset(name2_str,'0',strlen(name2));
	
	count = find_space(name1);
	strncpy(name1_str,name1,count);
	name1_str[count] = '\0';
	
	count = find_space(name2);
	strncpy(name2_str,name2,count);
	name2_str[count] = '\0';

	if(strcmp(name1_str,name2_str)<0)
		return(1);


	return(0);

	
}

int find_space(const char *str)
{
	int count,
		len;
	
	len = strlen(str);
	
	for(count=0;count<len;count++)
		if(str[count] == ' ')
			return(count);
	
	return(0);
}

