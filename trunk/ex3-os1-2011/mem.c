#include "mem.h"

// A function that allocate memory
//-----------------------------------------------------------------------------
// Input:		size of data structure needed
// Return:		pointer to data structure
char **alloc_cell(const int size)
{
    char **new_cell = NULL;      // create new pointer-pointer

    new_cell = (char**)malloc(sizeof(char*)*size) ;   // alloc memory

    if(new_cell == NULL)        // check if have memory
    	mem_error();			//	call memory error print

    return(new_cell);			//	return pointer to new data structure
    
}

//--------------------- FUNCTION ALLOCATE STRING MEMRY ------------------------
//	functin which allocate memory for string
//	if fail call to mem_error
//	input:	size of string size needed
char *alloc_string(const int size)
{
    char *new_str = NULL;      // create new pointer-pointer

    new_str = (char*)malloc(sizeof(char)*size) ;   // alloc memory

    if(new_str == NULL)        	// check if have memory
    	mem_error();			//	call memory error print
    	
    return(new_str);			//	return pointer to new string
    
}

//
// A function that free aloccated memory.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), number of strings at table.
void free_arr(char **data,const int len)
{
	int counter	=	0;			//	counter

	for(counter=0;counter<len;counter++)
		free(data[counter]);	//	free string in data structure
		
	free(data);
		
}

// A function that notify user about error  of aloccating memory.
//-----------------------------------------------------------------------------
void mem_error()
{
	perror("Can`t allocate memory.\n");		//	print message
	exit(EXIT_FAILURE);						//	exit whith error
	
}


// A function that copy tabel of strings.
//-----------------------------------------------------------------------------
// 	Input: new and old tabels of strings (type dubel pointer).
//	data_new 	-	new data structure
//	data_old	-	old data structure
void copy_arr(char **data_new,char **data_old,const int len)
{
	int counter;								// counter variable

	for(counter=0;counter<len;counter++)		//	copy data(pointers)
		data_new[counter] = data_old[counter];

}
