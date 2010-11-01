//#include <stdio.h>



#ifndef MEM_SEC
#define MEM_SEC

// A function that allocate memory
//-----------------------------------------------------------------------------
// Input:
// Output:
char **alloc_cell(const int size);

// A function that notify user about error  of aloccating memory.
//-----------------------------------------------------------------------------
void mem_error();

// A function that free aloccated memory.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), number of strings at table.
void free_arr(char **data, const int len);

#endif
