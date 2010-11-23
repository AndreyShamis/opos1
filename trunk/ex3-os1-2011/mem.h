//======================= DESCRIPTION =========================================
/*
 *	Memory functions
 *	This file give solutions for work with memory
 *	Included function for allocate memory [2]-char and [1]-char
 *	Also give function for delete from memory
 *	See functions description for more information.
 */
//========================= MEMORY TOOLS ======================================

#include <stdio.h>
#include <stdlib.h>

#ifndef MEM_SEC
#define MEM_SEC

// A function that allocate memory
//-----------------------------------------------------------------------------
// Input:		size of data structure needed
// Return:		pointer to data structure
char **alloc_cell(const int size);

//--------------------- FUNCTION ALLOCATE STRING MEMRY ------------------------
//	functin which allocate memory for string
//	if fail call to mem_error
//	input:	size of string size needed
char *alloc_string(const int size);


// A function that notify user about error  of aloccating memory.
//-----------------------------------------------------------------------------
void mem_error();

// A function that free aloccated memory.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), number of strings at table.
void free_arr(char **data, const int len);


#endif
