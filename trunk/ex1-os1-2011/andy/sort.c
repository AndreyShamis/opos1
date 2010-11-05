#include "sort.h"

// A function that sorting strings in tabel of data by name order.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), size of tabel - number of
// rows at tabel. (type integer).
void sort_by_name(char **data,const int size)
{
	int i, x;					//	counters for cicles

	for(i=0;i<size;i++)
		for(x=0;x<size;x++)
			if(cmpName(data[i],data[x]) == TRUE)//	compare strings
				swap_str(data,i,x);				//	swap strings
				
}

// A function that sorting strings in tabel of data by id order.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), size of tabel - number of
// rows at tabel. (type integer).
void sort_by_id(char **data,const int size)
{
	int i,x;		//	counters for cicles

	int id1_len	=	0,		//	len of digits in first string
	 	id2_len	=	0;		//	len of digits in second string
	int sp_pos1	=	0,		//	find space position var in first string
		sp_pos2	=	0;		//	find space position var in second string
	

	for(i=0;i<size;i++)
		for(x=0;x<size;x++)
		{
			sp_pos1		=	find_space(data[i]);
			sp_pos2		=	find_space(data[x]);
			
			//	set number to first digit in strings after space			
			id1_len = strlen((data[i])+sp_pos1);
			id2_len = strlen((data[x])+sp_pos2);
			
			// 	if lentgh of id in first string snaller then in second string
			//	swap between strings
			//	but see README in section TODO-1
			if(id1_len < id2_len)
				swap_str(data,i,x);
			//	if strings lentghs in two strings ==
			//	chack alphabetic compare only on digits
			else if(id1_len == id2_len 
			&& strcmp((data[i])+sp_pos1,(data[x])+sp_pos2) <0)
				swap_str(data,i,x);		//	swap stings
			
		}

}

// A function that compare names (alfamerik strings)
//-----------------------------------------------------------------------------
// Input: Two pointers to string that include names information that located in
// data tabel (type *char).
// Return true if name1 smaller then name2, atherwise return false
// (type int).
int cmpName(const char *name1,const char *name2)
{

	int count;							//	counter in space search

	char name1_str[MAX_STR_LEN];		//	string for name only
	char name2_str[MAX_STR_LEN];		//	string for name only
	
	//	fill strings whith 0
	memset(name1_str,'0',strlen(name1));
	memset(name2_str,'0',strlen(name2));

	//	found space in first string
	count = find_space(name1);
	//	copy string 
	strncpy(name1_str,name1,count);
	//	add nulterminated sinbol
	name1_str[count] = '\0';
	
	//	found space in first string
	count = find_space(name2);
	//	copy string 
	strncpy(name2_str,name2,count);
	//	add nulterminated sinbol
	name2_str[count] = '\0';

	if(strcmp(name1_str,name2_str)<0)	//	compare strings
		return(TRUE);					//	return true

	return(FALSE);						//	return false
	
}

// A function that swap between tow strings that located in 2D tabel.
// strin = line in tabel.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), first and second strings (that
// need to be swap) location in tabel (type: integers).
void swap_str(char **str,const int fir,const int sec)
{
	char *temp;			//	temp variable

	temp = str[fir];	//	this block swap
	str[fir]=str[sec];	// 	between two
	str[sec]=temp;		//	strings in array

}

// A function that find "space" charecter in string.
//----------------------------- FIND SPACE ------------------------------------
// Input: 	Pointer to string which locate in data tabel (type *char).
// Return: 	index of space in string (type int).
int find_space(const char *str)
{
	int count	=	0,		//	counter	
		len		=	0;		//	lentgh of string geted	

	len = strlen(str);		//	get lentgh of string

	//	start search space
	for(count=0;count<len;count++)
		if(str[count] == ' ')		//	check if this simbol is space
			return(count);			//	return position

	return(0);						//	return 0 
	
}

