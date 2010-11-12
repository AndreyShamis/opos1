#include "utils.h"
#include <string.h>

#ifndef SORT_SEC
#define SORT_SEC


// A function that find "space" charecter in string.
//----------------------------- FIND SPACE ------------------------------------
// Input: 	Pointer to string which locate in data tabel (type *char).
// Return: 	index of space in string (type int).
int find_space(const char *str);

// A function that swap between tow strings that located in 2D tabel.
// strin = line in tabel.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), first and second strings (that
// need to be swap) location in tabel (type: integers).
void swap_str(char **str, const int fir, const int sec);

// A function that compare names (alfamerik strings)
//-----------------------------------------------------------------------------
// Input: Two pointers to string that include names information that located in
// data tabel (type *char).
// Return true if name1 smaller then name2, atherwise return false
// (type int).
int cmpName(const char *name1, const char *name2);


// A function that sorting strings in tabel of data by id order.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), size of tabel - number of
// rows at tabel. (type integer).
void sort_by_id(char **data, const int size);

// A function that sorting strings in tabel of data by name order.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), size of tabel - number of
// rows at tabel. (type integer).
void sort_by_name(char **data, const int size);

#endif
