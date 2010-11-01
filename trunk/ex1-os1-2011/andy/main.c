/*
 * EX1 :: A program that manage data base of name's and id's.
 * ===========================================================================
 * Writen by: Andrey Shamis,  id: 321470882, login: andreysh
 * and:       Ilia Gaisinsky, id: 309480051, login: iliaga
 * Input:  text file that include names and ids, sort key.
 * Output: Text file that include names and ids, Dipend on input sort key:
 * Key    | sort method
 *---------------------
 * "name" | by name
 *---------------------
 *  "id"  | by id
 *---------------------
 */

//                               Include section
//=============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mem.h"

//                                Const cection
//=============================================================================
#define MAX_STR_LEN  200
#define MAX_MENU_STR_LEN 5


//#############################################################################
//------------------------------ Sort By NAME ---------------------------------



void print_arr( char **data,const int size)
{
	int i=0;
	
	for(i=0;i<size;i++)
	{
		
		printf("%s.",data[i]);
		printf("\n");
	}
	printf("\n\n");
}
//#############################################################################


//                             Prototypes section
//=============================================================================


void incorect_param();


// A function that read text file.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), counter of strings (type
// &char),      #############Miss(FILE&)#####################
char  **readFile(FILE *fRead,int *str_counter);



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

// A function that locate and convert string of digits to integer.
//-----------------------------------------------------------------------------
// Input: Pointer to sting(type *char) and start point to locate digits
// (type int).
// Output: id (type int).
int popID(const char *str,const int start);

// A function that get id from string that include mixed data (not only ids).
//-----------------------------------------------------------------------------
// Input: Pointer to string from tabel (type *char).
// Output: id (type int).
int getID(const char *str);

// A function that copy tabel of strings.
//-----------------------------------------------------------------------------
// Input: new and old tabels of strings (type dubel pointer).
void copy_arr(char **data_new,char **data_old,const int len);

// A function that find "space" charecter in string.
//-----------------------------------------------------------------------------
// Input: Pointer to string which locate in data tabel (type *char).
// Output: index of space in string (type int).
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
// Output: Return "1" if name1 smaller then name2, atherwise return "0"
// (type int).
int cmpName(const char *name1, const char *name2);


//                                Main section
//=============================================================================
int main(int argc, char *argv[])
{
    // Difine sort key.
	char key[MAX_MENU_STR_LEN];

    // Difine tabel of data.
	char 	**dataDB=NULL;
	 		//**temp=NULL,
			//*str=NULL;


	FILE *fRead;		//	Var for red file.
	FILE *fWrite;		// 	Var for write file.

    // Difine counter of strings at tabel.
	int str_counter=0;

    // If the user enter nesesery data corect:
	if(argc == 3 )
	{
        // Open read and write fils.
		fRead = fopen(argv[1],"r");
		fWrite = fopen(argv[2],"w");

        // If failed to opening read file.
		if(fRead == NULL)
            // Error notepy of opening read file.
			printf("Can`t read file %s \n", argv[1]);
		else
		{
		    // Read file and transform the data to tabel of strings.
			dataDB=readFile(fRead,&str_counter);
			
			// Close readed file.
			fclose(fRead);

            // Get sort type.

            // Print the tabel of syrings.
			print_arr(dataDB,str_counter);
			
			scanf("%s",key);

			// Check sort type.
			if(!strcmp(key,"name"))
				sort_by_name(dataDB,str_counter);	//	sort by name
			else if(!strcmp(key,"id"))
				sort_by_id(dataDB,str_counter);		// sort by id

			print_arr(dataDB,str_counter);


			//start write to file section
				//TODO
				//TODO
				//TODO
			//end write to file section

			//print_arr(dataDB, str_counter);

            // Close writed file.
			fclose(fWrite);

            // free aloccated Memory
			free_arr(dataDB, str_counter);
			free(dataDB);

		}
	}
	// Tell user how to enter data - corect.
	else
		incorect_param();

	return(1);
}

//                             Function section
//==============================================================================



//------------------------------- Incorrect param------------------------------

void incorect_param()
{
	printf("You need enter 2 parameters:\n");
	printf("1. Read file name\n");
	printf("2. Write file name\n");

}

// A function that read text file.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), counter of strings (type
// &char),      #############Miss(FILE&)#####################
char **readFile(FILE *fRead,int *str_counter)
{
	char **temp=NULL, **dataDB=NULL;
	char data[MAX_STR_LEN];
	char *str=NULL;

	while(fgets(data,MAX_STR_LEN,fRead) != NULL)	// TODO CONST
	{
		str = (char*)malloc( (sizeof(char)*strlen(data))+1);

		
		temp = alloc_cell((*str_counter)+1);
		
		copy_arr(temp,dataDB,*str_counter);
		free(dataDB);
		dataDB = temp;
		temp = NULL;
		strcpy(str,data);
		dataDB[(*str_counter)] = str;

		(*str_counter)++;
	}
	
	return(dataDB);
}



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

	for(i=0;i<size;i++)
	{
		//getID(data[i]);
		for(x=0;x<size;x++)
			if(getID(data[i])<getID(data[x]))
				swap_str(data,i,x);
	}
}

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

// A function that copy tabel of strings.
//-----------------------------------------------------------------------------
// Input: new and old tabels of strings (type dubel pointer).
void copy_arr(char **data_new,char **data_old,const int len)
{
	int i;

	for(i=0;i<len;i++)
		data_new[i] = data_old[i];
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


