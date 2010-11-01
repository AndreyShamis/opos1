#include "mem.h"

// A function that allocate memory
//-----------------------------------------------------------------------------
// Input:
// Output:
char **alloc_cell(const int size)
{
    char **new_cell = NULL;      // create new pointer-pointer

    new_cell = (char**)malloc(sizeof(char*)*size) ;   // alloc memory

    if(new_cell == NULL)        // check if have memory
    	mem_error();

    return(new_cell);
}

// A function that free aloccated memory.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), number of strings at table.
void free_arr(char **data,const int len)
{
	int i;

	for(i=0;i<len;i++)
		free(data[i]);
}



// A function that notify user about error  of aloccating memory.
//-----------------------------------------------------------------------------
void mem_error()
{
	printf("Can`t allocate memory.\n");
}

