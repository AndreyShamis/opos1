/*
 * EX1 :: A program that manage data base of name's and id's.
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
 * "name" | by name
 *---------------------
 *  "id"  | by id
 *---------------------
 *
 *		to compile : make
 *
 *		to run:	./ex1 <INPUT FILE> <OUTPUT FILE>
 *		example-1:	./ex1 in2.txt id.txt
 *					id
 *
 *		example-2:	./ex1 in2.txt name.txt
 *					name
 *
 */

//                               Include section
//=============================================================================
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "mem.h"
#include "sort.h"
#include "read.h"
#include "write.h"
#include "utils.h"
#include <string.h>


//                             Prototypes section
//=============================================================================

//------------------------------- Incorrect param------------------------------
//	print message of incorrect input parameters
void incorect_param();

//------------------------------ OPEN FILES -----------------------------------
//	input files desc to file to read and file to write
//	return	false if cant open any of file
//			true if all files is opened
int ifFileOpen(FILE *fRead, FILE *fWrite);

//-------------------------- SORT CALL ----------------------------------------
//	function which call to sort method
//	input 	data structure
//			data counter in data structure
//			type of sort
void sort(char **dataDB,const int str_counter,char key[]);

//-------------------------- Sun Sort------------------------------------------
//	function which
//	input
void sonSort(char **dataDB, int str_counter, char *inputFileName, int son);

//-------------------------- Print file------------------------------------------
//	function which
//	input
void printFile(int son);



//======================== END OF PROTOTYPE ===================================

//                                Main section
//=============================================================================
int main(int argc, char *argv[])
{

	char 	**dataDB	=	NULL;	    // 	Difine tabel of data.
	//char key[MAX_MENU_STR_LEN];			// Difine sort key.



	int str_counter	=	0;	// Difine counter of strings at tabel.

	int printType = atoi(argv[2]);

    // If the user enter nesesery data corect:
	if(argc == 3 )
	{

        pid_t status;

        int i;

        for(i= 0; i< 2; i++)
        {
            status = fork();
            if(status < 0)
            {
                fputs("error in fork", stderr);
                exit(EXIT_FAILURE);
            }
            else if(status == 0)

                sonSort(dataDB, str_counter, argv[1], i);


            wait(&status);
        }

        if(printType == 1)
        {
            for(i= 0; i< 2; i++)
            {
                status = fork();

                if(status < 0)
                {
                    fputs("error in fork", stderr);
                    exit(EXIT_FAILURE);
                }
                else if(status == 0)
                {
                    printFile(i);
                }
                else
                {
                    wait(&status);
                }
            }
            wait(&status);

            //for(i= 0; i< 2; i++)
           // {
             //   wait(&status);
            //}
        }

        else
        {
            status = fork();
            if(status < 0)
            {
                fputs("error in fork", stderr);
                exit(EXIT_FAILURE);
            }
            else if(status == 0)
            {
                printFile(1);
            }
            wait(&status);

            status = fork();
            if(status < 0)
            {
                fputs("error in fork", stderr);
                exit(EXIT_FAILURE);
            }
            else if(status == 0)
            {
                printFile(2);
            }
            wait(&status);
        }
    }
	else
								// Tell user how to enter data - corect.
		incorect_param();						//	print error

	return(EXIT_SUCCESS);						//	exit from program

}


//                             Function section
//=============================================================================


//------------------------------ OPEN FILES -----------------------------------
//	input files desc to file to read and file to write
//	return	false if cant open any of file
//			true if all files is opened
int ifFileOpen(FILE *fRead, FILE *fWrite)
{
    // If failed to opening read file.
	if(fRead == NULL)
    {
        // Error notepy of opening read file.
		printf("Can`t read input file. \n");
		return(FALSE);
	}
	else if(fWrite == NULL)
	{
		//	print message of error open file to write
		printf("Can`t write to file. \n");
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
	printf("2. Write file name\n");

}

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

//-------------------------- Sun Sort------------------------------------------
//	function which
//	input
void sonSort(char **dataDB, int str_counter, char *inputFileName, int son)
{
    FILE *fRead		=	NULL;			//	Var for red file.
	FILE *fWrite	=	NULL;			// 	Var for write file.


    char str[MAX_MENU_STR_LEN];

    if(son == 0)
    {

        strcopy(str, "id")
        fWrite = fopen("id.out","w");
    }
    else
    {
        strcopy(str, "name")
        fWrite = fopen("name.out","w");
    }

    fRead = fopen(inputFileName,"r");	// Open read and write fils.

    if(ifFileOpen(fRead,fWrite))
    {
        // Read file and transform the data to tabel of strings.
        dataDB= readLines(fRead, &str_counter);
        fclose(fRead);						// Close readed file.

        sort(dataDB, str_counter, str);		//	SORT


        writeFile(fWrite, str_counter, dataDB);//	write to file sorted data
        fclose(fWrite);						// Close writed file.

        //	FREE MEMORY
        free_arr(dataDB, str_counter);		// free aloccated Memory
        free(dataDB);						// free data structure

    }
}

//-------------------------- Print file------------------------------------------
//	function which
//	input
void printFile(int son)
{
    char = fileName[MIN_STR_LEN];

    if(son == 1)

        fileName = "name.out";
    else

        fileName = "id.out";


    if(execlp("cat", "cat", fileName, NULL)
    {
        perror("exaclp() faild");

        exit(EXIT_FAILURE);
    }
}


