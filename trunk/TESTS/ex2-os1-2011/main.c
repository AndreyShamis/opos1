/*
 * EX2:: A program that manage data base of name's and id's.
 * ===========================================================================
 * Writen by: Andrey Shamis,  id: 321470882, login: andreysh
 * and:       Ilia Gaisinsky, id: 309480051, login: iliaga
 * Input:	1: 	SORT TYPE (id/name)  
 *			2:	additional data(<Name><_[space]><id>)
 * Input in parameters:
 *			text file that include names and ids.
 * Output: Text file that include names and ids, Dipend on input sort key:
 * Key    | sort method
 *---------------------
 * "2" | by name
 *---------------------
 *  "1"  | by id
 *---------------------
 *
 *		to compile : make
 *
 *		to run:	./ex2 <INPUT FILE> <SORT TYPE>
 *		example-1:	./ex2 in2.txt 1
 *					id
 *					
 *		example-2:	./ex2 in2.txt 2
 *					name
 *
 */

//                               Include section
//=============================================================================
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "mem.h"
#include "sort.h"
#include "read.h"
#include "write.h"
#include "utils.h"




//                             Prototypes section
//=============================================================================

//------------------------------- Incorrect param------------------------------
//	print message of incorrect input parameters
void incorect_param();

//------------------------------ OPEN FILES -----------------------------------
//	input file desc to file wonts be open 
//	return	false if cant open  file
//			true if is opened
int ifFileOpen(FILE *ffile);


/*
//-------------------------- SORT CALL ----------------------------------------
//	function which call to sort method
//	input 	data structure
//			data counter in data structure
//			type of sort
void sort(char **dataDB,const int str_counter,char key[]);
*/

//======================== END OF PROTOTYPE ===================================

//                                Main section
//=============================================================================
int main(int argc, char *argv[])
{

	char 	**dataDB	=	NULL;	    // 	Difine tabel of data.
	//char key[MAX_MENU_STR_LEN];			// Difine sort key.

	FILE *fRead		=	NULL;			//	Var for red file.
	FILE *fWr_id	=	NULL;			// 	Var for write file id.
   	FILE *fWr_name	=	NULL;			// 	Var for write file name.
    	
	int str_counter	=	0;	// Difine counter of strings at tabel.

	int id_son;

    // If the user enter nesesery data corect:
	if(argc == 3 )
	{
		//scanf("%s",key);	    				// Get sort type.
	   	fRead 	= 	fopen(argv[1],"r");			// Open read and write fils.
		fWr_id 	= 	fopen("id.out","w");
		fWr_name = 	fopen("name.out","w");

		if(ifFileOpen(fRead) && ifFileOpen(fWr_id) && ifFileOpen(fWr_name))
		{
		    // Read file and transform the data to tabel of strings.
			dataDB=readLines(fRead,&str_counter);
			fclose(fRead);						// Close readed file.
			// Check sort type.
//			if(argv[2][0] == '1')
//				sort_by_name(dataDB,str_counter);	//	sort by name
//			else if(argv[2][0] == '2')
//				sort_by_id(dataDB,str_counter);		// sort by id
///
//			sort(dataDB,str_counter,key);		//	SORT
			
			int soncounter = 0;

			soncounter++;
			pid_t status = fork();
			
			
			if(status == 0)
			{
				soncounter++;
				status = fork();
										
			}
			
			if(status > 0)
			{
				if(soncounter == 1)
				{
					printf("Sort by ID\n");
					sort_by_id(dataDB,str_counter);	//	sort by name
					writeFile(fWr_id,str_counter,dataDB);//	write to file sorted data
				
				}
				else if(soncounter == 2)
				{
					printf("Sort by NAME\n");
					sort_by_name(dataDB,str_counter);		// sort by id
					writeFile(fWr_name,str_counter,dataDB);//	write to file sorted data		
				}
			}

			
			fclose(fWr_id);						// Close writed file.
			fclose(fWr_name);					// Close writed file.

			id_son = wait(&status);
			if(id_son > 0 && argv[2][0] == '2')
			{
				//printf("Son %d ended. exitstatus = %d\n", id_son, WEXITSTATUS(status));
		
				if(soncounter == 1)		
					execlp("cat" ,"cat","id.out",NULL);
				else
					execlp("cat" ,"cat","name.out",NULL);
		
			}
			else if(id_son > 0 && argv[2][0] == '1')
			{
			
		
					execlp("cat" ,"cat","id.out",NULL);
					execlp("cat" ,"cat","name.out",NULL);
		
			
			}
				
			if(status == 0)
				printf("THE END\n");
		
			
			
     		//	FREE MEMORY
			free_arr(dataDB, str_counter);		// free aloccated Memory
			free(dataDB);						// free data structure

		}
	}
	else							// Tell user how to enter data - corect.
		incorect_param();						//	print error

	return(EXIT_SUCCESS);						//	exit from program

}

//                             Function section
//=============================================================================


//------------------------------ OPEN FILES -----------------------------------
//	input file desc to file wonts be open 
//	return	false if cant open  file
//			true if is opened
int ifFileOpen(FILE *ffile)
{
    // If failed to opening read file.
	if(ffile == NULL)
    {
        // Error notepy of opening read file.
		printf("Can`t open file. \n");
		return(FALSE);
	}

	return(TRUE);					//	FILES OPEN SUCCESS

}

//------------------------------- Incorrect param------------------------------
//	print message of incorrect input parameters
void incorect_param()
{
	printf("You need enter 2 parameters:\n");
	printf("1. Read file name\n");
	printf("2. Sort Type : 1-id / 2-name\n");

}

/*
//-------------------------- SORT CALL ----------------------------------------
//	function which call to sort method
//	input 	data structure
//			data counter in data structure
//			type of sort
void sort(char **dataDB,const int str_counter,char key[])
{

	// Check sort type.
	if(!strcmp(key,"name"))
		sort_by_name(dataDB,str_counter);	//	sort by name
	else if(!strcmp(key,"id"))
		sort_by_id(dataDB,str_counter);		// sort by id

}
*/

