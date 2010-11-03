/*
 * EX1 :: A program that manage data base of name's and id's.
 * ===========================================================================
 * Writen by: Andrey Shamis,  id: 321470882, login: andreysh
 * and:       Ilia Gaisinsky, id: 309480051, login: iliaga
 * Input:  text file that include names and ids, sort key.
 * Output: Text file that include names and ids, Dipend on input sort key:
 * Key    | sort method
 *---------------------
 * "name" | by name
 *---------------------
 *  "id"  | by id
 *---------------------
 */

//                               Include section
//=============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem.h"
#include "sort.h"
#include "read.h"
#include "write.h"

//                                Const cection
//=============================================================================
#define MAX_STR_LEN  200
#define MAX_MENU_STR_LEN 5


//#############################################################################
//------------------------------ Sort By NAME ---------------------------------



void print_arr( char **data,const int size)
{
	int i=0;
	
	for(i=0;i<size;i++)
	{
		
		printf("%s.",data[i]);
		printf("\n");
	}
	printf("\n\n");
}

void print_arr_t( char **data,const int size)
{
	int i=0,x=0;
	
	for(i=0;i<size;i++)
	{
		for(x=0;x<strlen(data[i]);x++)
		{	
			if(data[i][x] == ' ')
				printf("\r\t\t\t\t");
				
			printf("%c",data[i][x]);
			
		}
		printf("\n");
	}
	printf("\n\n");
}
//#############################################################################


//                             Prototypes section
//=============================================================================

void incorect_param();

void menu(char **dataDB,const int str_counter)
{
    // Difine sort key.
	char key[MAX_MENU_STR_LEN];

	scanf("%s",key);

	// Check sort type.
	if(!strcmp(key,"name"))
		sort_by_name(dataDB,str_counter);	//	sort by name
	else if(!strcmp(key,"id"))
		sort_by_id(dataDB,str_counter);		// sort by id

}

//                                Main section
//=============================================================================
int main(int argc, char *argv[])
{


    // Difine tabel of data.
	char 	**dataDB=NULL;

	FILE *fRead;		//	Var for red file.
	FILE *fWrite;		// 	Var for write file.

    // Difine counter of strings at tabel.
	int str_counter=0;

    // If the user enter nesesery data corect:
	if(argc == 3 )
	{
        // Open read and write fils.
		fRead 	= 	fopen(argv[1],"r");
		fWrite 	= 	fopen(argv[2],"w");

        // If failed to opening read file.
		if(fRead == NULL)
            // Error notepy of opening read file.
			printf("Can`t read file %s \n", argv[1]);
		else if(fWrite == NULL)
			printf("Can`t write to file %s \n",argv[2]);
		else
		{
		    // Read file and transform the data to tabel of strings.
			dataDB=readFile(fRead,&str_counter);
			
			// Close readed file.
			fclose(fRead);

            // Get sort type.

            // Print the tabel of syrings.
			print_arr(dataDB,str_counter);			
			menu(dataDB,str_counter);
			print_arr_t(dataDB,str_counter);
			
			writeFile(fWrite,str_counter,dataDB);
            // Close writed file.
			fclose(fWrite);

            // free aloccated Memory
			free_arr(dataDB, str_counter);
			free(dataDB);

		}
	}
	// Tell user how to enter data - corect.
	else
		incorect_param();

	return(1);
}

//                             Function section
//==============================================================================



//------------------------------- Incorrect param------------------------------

void incorect_param()
{
	printf("You need enter 2 parameters:\n");
	printf("1. Read file name\n");
	printf("2. Write file name\n");

}
