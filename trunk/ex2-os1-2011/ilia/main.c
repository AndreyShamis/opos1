/*
 * EX2:: A program that manage data base of name's and id's.
 * makes two child for read and sort data
 * and makes two child 
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
 * "2"  | random
 *---------------------
 * "1"  | series
 *---------------------
 *
 *		to compile : make
 *
 *		to run:	./ex2 <INPUT FILE> <SORT TYPE>
 *		example-1:	./ex2 in2.txt 1
 *					
 *		example-2:	./ex2 in2.txt 2
 *	
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
int ifFileOpen(FILE *fFile);

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

//--------------------Print sons in series order-------------------------------
//	function which
//	input
void sonsPrintSeries();

//--------------------Print sons in random order-------------------------------
//	function which
//	input
void sonsPrintRandom();


//-------------------------- Print file----------------------------------------
//	function which
//	input
void printFile(int son);

//-------------------------- Chek fork error-----------------------------------
//	function which
//	input
void chekForkError(pid_t *status);

//-------------------------- Wait sons-----------------------------------------
//	function which
//	input
void waitSons(pid_t *status);

//======================== END OF PROTOTYPE ===================================

//                                Main section
//=============================================================================
int main(int argc, char *argv[])
{

	pid_t status;
	char 	**dataDB	=	NULL;	    // Difine tabel of data.
	int str_counter		=	0;			// Difine counter of strings at tabel.
	int printType 		= atoi(argv[2]);// Type of oreder print
	int sonCoun;

    // If the user enter nesesery data corect:
	if(argc == NUMBER_PARAM)
	{

		for(sonCoun= SON1; sonCoun<= NUMBER_SONS; sonCoun++)
		{
			status = fork();

			chekForkError(&status);

			if(!status)

				sonSort(dataDB, str_counter, argv[1], sonCoun);
		}

		waitSons(&status);

        if(printType == RANDOM)

        	sonsPrintRandom();


        else if(printType == SERIES)

        	sonsPrintSeries();

        printf("THE END\n");
    }
	else
								// Tell user how to enter data - corect.
		incorect_param();						//	print error

	return(EXIT_SUCCESS);						//	exit from program

}


//                             Function section
//=============================================================================


//------------------------------ OPEN FILES -----------------------------------
//	input files desc to file
//	return	false if cant open file
//			true if is opened
int ifFileOpen(FILE *fFile)
{
    // If failed to opening file.
	if(fFile == NULL)
    {
        // Error notepy of opening file.
		printf("Can`t open file. \n");
		return(FALSE);
	}

	return(TRUE);					//	FILE OPEN SUCCESS

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

    if(son == SON1)
    {

        strcpy(str, "id");
        fWrite = fopen("id.out","w");
    }
    else
    {
        strcpy(str, "name");
        fWrite = fopen("name.out","w");
    }

    fRead = fopen(inputFileName,"r");	// Open read and write fils.

    if(ifFileOpen(fRead) && ifFileOpen(fWrite))
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
    exit(EXIT_SUCCESS);
}

//--------------------Print sons in series order-------------------------------
//	function which
//	input
void sonsPrintSeries()
{
	pid_t status;

	status = fork();

	chekForkError(&status);

	if(!status)

		printFile(SON1);

	else

		wait(&status);


	status = fork();

	chekForkError(&status);

	if(!status)

		printFile(SON2);

	else

		wait(&status);
}

//--------------------Print sons in random order-------------------------------
//	function which
//	input
void sonsPrintRandom()
{
	pid_t status;
	int sonCoun;

	for(sonCoun= SON1; sonCoun<= NUMBER_SONS; sonCoun++)
	{
		status = fork();

		chekForkError(&status);

		if(!status)
			printFile(sonCoun);
	
	}
	
	waitSons(&status);

}

//-------------------------- Print file----------------------------------------
//	function which
//	input
void printFile(int son)
{
    char fileName[MIN_STR_LEN];

    if(son == SON1)
        strcpy(fileName, "id.out");
    else
        strcpy(fileName, "name.out");

	
    if(execlp("cat", "cat", fileName, NULL))
    {
        perror("exaclp() faild");

        exit(EXIT_FAILURE);
    }
    else
    	exit(EXIT_SUCCESS);

}


//-------------------------- Chek fork error-----------------------------------
//	function which	get pointer to pid_t status of fork
//	and if can not fork do exit with error
void chekForkError(pid_t *status)
{
	if(*status < 0)
	{
		perror("FORK - error\n");
		exit(EXIT_FAILURE);
	}
	
}

//-------------------------- Wait sons-----------------------------------------
//	function which waiting for son with pid_t provided by ststus 
//	input	pointer to pid_t status 
void waitSons(pid_t *status)
{
	int counter;						//	counter variable
	
	//	for NUMBERS of SONS	wa
	for(counter= 0; counter< NUMBER_SONS; counter++)
		wait(status);
            	
}

