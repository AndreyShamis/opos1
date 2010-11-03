#include <stdio.h>
#include "sort.h"

// A function that sorting strings in tabel of data by name order.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), size of tabel - number of
// rows at tabel. (type integer).
void sort_by_name(char **data,const int size)
{
	int i, x;

	for(i=0;i<size;i++)
	{
		for(x=0;x<size;x++)
		{
			if(cmpName(data[i],data[x]) ==1)
			{
				swap_str(data,i,x);
			}
		}
	}
}

// A function that sorting strings in tabel of data by id order.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), size of tabel - number of
// rows at tabel. (type integer).
void sort_by_id(char **data,const int size)
{
	int i,x;

	int id1_len;
	int id2_len;
	

	for(i=0;i<size;i++)
	{
		//getID(data[i]);
		for(x=0;x<size;x++)
		{
			id1_len = strlen((data[i]) + find_space(data[i]) );
			id2_len = strlen((data[x])+find_space(data[x]));
			if(id1_len < id2_len)
			{
//				printf("1: %s - \n",(data[i])+find_space(data[i]));
//				printf("2: %s - \n",(data[x])+find_space(data[x]));
				swap_str(data,i,x);
			}
			else if(id1_len == id2_len && strcmp((data[i])+find_space(data[i]),(data[x])+find_space(data[x])) <0)
			{
				swap_str(data,i,x);;
			}
				

		}
	}
}

/*
// A function that get id from string that include mixed data (not only ids).
//-----------------------------------------------------------------------------
// Input: Pointer to string from tabel (type *char).
// Output: id (type int).
int getID(const char *str)
{
	int count,
		result;
		
	int len = strlen(str);
	
	for(count=0;count<len;count++)
		if(str[count] == ' ')
		{
			result = popID(str,count+1);
			break;
		}

	return(result);
}

// A function that locate and convert string of digits to integer.
//-----------------------------------------------------------------------------
// Input: Pointer to sting(type *char) and start point to locate digits
// (type int).
// Output: id (type int).
int popID(const char *str,const int start)
{
	int count,
		i=0;
	int len=strlen(str);

	char temp[MAX_STR_LEN];

	for(count=start;count<len;count++)
		if(isdigit(str[count]))
		{
			temp[i]=str[count];
			i++;
		}
		else
		{
			temp[i] = '\0';
			break;

		}

	return(atoi(temp));
}

*/

// A function that compare names (alfamerik strings)
//-----------------------------------------------------------------------------
// Input: Two pointers to string that include names information that located in
// data tabel (type *char).
// Output: Return "1" if name1 smaller then name2, atherwise return "0"
// (type int).
int cmpName(const char *name1,const char *name2)
{

	int count;

	char name1_str[MAX_STR_LEN];
	char name2_str[MAX_STR_LEN];
	
	memset(name1_str,'0',strlen(name1));
	memset(name2_str,'0',strlen(name2));

	count = find_space(name1);
	strncpy(name1_str,name1,count);
	name1_str[count] = '\0';

	count = find_space(name2);
	strncpy(name2_str,name2,count);
	name2_str[count] = '\0';

	if(strcmp(name1_str,name2_str)<0)
		return(1);

	return(0);
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
//-----------------------------------------------------------------------------
// Input: Pointer to string which locate in data tabel (type *char).
// Output: index of space in string (type int).
int find_space(const char *str)
{
	int count,
		len;

	len = strlen(str);

	for(count=0;count<len;count++)
		if(str[count] == ' ')
			return(count);

	return(0);
}

