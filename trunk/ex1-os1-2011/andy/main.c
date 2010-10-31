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

//                                Const cection
//=============================================================================
#define MAX_STR_LEN  200
#define MAX_MENU_STR_LEN 5

//------------------------------ Sort By NAME ---------------------------------



void print_arr( char **data,const int size)
{
	int i;

	for(i=0;i<size;i++)
	{
		printf("%s.",data[i]);
		printf("\n");
	}
}


//                             Prototypes section
//=============================================================================


// A function that copy tabel of strings.
//-----------------------------------------------------------------------------
// Input: new and old tabels of strings (type dubel pointer).
void copy_arr(char **data_new,char **data_old,int len);

// A function that allocate
//-----------------------------------------------------------------------------
// Input:
// Output:
char **alloc_cell(const int size);

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

// A function that find "space" charecter in string.
//-----------------------------------------------------------------------------
// Input: Pointer to string which locate in data tabel (type *char).
// Output:
int find_space(const char *str);

// A function that swap between tow strings that located in 2D tabel.
// strin = line in tabel.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), first and second strings (that
// need to be swap) location in tabel (type: integers).
void swap_str(char **str,const int fir,const int sec);

// A function that compare names (alfamerik strings)
//-----------------------------------------------------------------------------
// Input: Two pointers to string that include names information that located in
// data tabel (type *char).
// Output: Return "1" if name1 smaller then name2, atherwise return "0"
// (type int).
int cmpName(const char *name1,const char *name2);



// A function that sorting strings in tabel of data by name order.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), size of tabel - number of
// rows at tabel. (type integer).
void sort_by_name(char **data,const int size);


// A function that sorting strings in tabel of data by id order.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), size of tabel - number of
// rows at tabel. (type integer).
void sort_by_id(char **data,const int size);

// A function that
//-----------------------------------------------------------------------------
// Input:
// Output:
void mem_error();

// A function that
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer),
// Output:
void free_arr(char **data,const int len);

// A function that
//-----------------------------------------------------------------------------
// Input:
// Output:
void readFile(FILE& fRead,int& str_counter,char **dataDB);

//                                Main section
//=============================================================================
int main(int argc, char *argv[])
{

	char key[MAX_MENU_STR_LEN];


	char 	**dataDB=NULL;
	 		//**temp=NULL,
			//*str=NULL;

	FILE *fRead;		//	Var for red file
	FILE *fWrite;		// 	Var for write file

	int str_counter=0;

	if(argc == 3 )
	{

		fRead = fopen(argv[1],"r");
		fWrite = fopen(argv[2],"w");

		if(fRead == NULL)
			printf("Can`t read file %s \n", argv[1]);
		else
		{
			readFile(fRead,str_counter,dataDB);
			/*
			while(fgets(data,MAX_STR_LEN,fRead) != NULL)	// TODO CONST
			{
				str = (char*)malloc( (sizeof(char)*strlen(data) +1 ));

				temp = alloc_cell(str_counter+1);
				copy_arr(temp,dataDB,str_counter);
				free(dataDB);
				dataDB = temp;

				strcpy(str,data);
				dataDB[str_counter] = str;

				str_counter++;

			}

			*/
			fclose(fRead);			// close readed file

			scanf("%s",key);		// Get sort type

			print_arr(dataDB,str_counter);
			printf("\n\n");

			// Check sort type section
			if(!strcmp(key,"name"))
				sort_by_name(dataDB,str_counter);	//	sort by name
			else if(!strcmp(key,"id"))
				sort_by_id(dataDB,str_counter);		// sort by id
			// end sort section


			//start write to file section
				//TODO
				//TODO
				//TODO
			//end write to file section

			print_arr(dataDB,str_counter);

			fclose(fWrite);			// close writed file

			free_arr(dataDB,str_counter);
			free(dataDB);

		}
	}
	else
	{
		printf("You need enter 2 parameters:\n");
		printf("1. Read file name\n");
		printf("2. Write file name\n");
	}

	return(1);
}


void readFile(FILE& fRead,int& str_counter,char **dataDB)
{
	char **temp=NULL;
	char data[MAX_STR_LEN];
	char *str=NULL;

	while(fgets(data,MAX_STR_LEN,fRead) != NULL)	// TODO CONST
	{
		str = (char*)malloc( (sizeof(char)*strlen(data) +1 ));

		temp = alloc_cell(str_counter+1);
		copy_arr(temp,dataDB,str_counter);
		free(dataDB);
		dataDB = temp;

		strcpy(str,data);
		dataDB[str_counter] = str;

		str_counter++;

	}
}
//------------------------- SWAP ----------------------------------------------
// Start swap function
void swap_str(char **str,const int fir,const int sec)
{
	char *temp;			//	temp variable

	temp = str[fir];	//	this block swap
	str[fir]=str[sec];	// 	between two
	str[sec]=temp;		//	strings in array

}
//	End swap function

void mem_error()
{
	printf("Can`t allocate memory.\n");

}

//------------------------- Sort by name --------------------------------------
// this function sorting strings in array data by name order
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

void free_arr(char **data,const int len)
{
	int i;

	for(i=0;i<len;i++)
		free(data[i]);

}

char **alloc_cell(const int size)
{
    char **new_cell = NULL;      // create new pointer-pointer

    new_cell = (char**)malloc(sizeof(char*)*size) ;   // alloc memory

    if(new_cell == NULL)        // check if have memory
    	mem_error();

    return(new_cell);

}

void copy_arr(char **data_new,char **data_old,int len)
{
	int i;

	for(i=0;i<len;i++)
		data_new[i] = data_old[i];

}


//------------------------------ Sort By ID -----------------------------------
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


int popID(const char *str,const int start)
{
	int count,
		i=0;
	int len=strlen(str);

	char temp[len];

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

int cmpName(const char *name1,const char *name2)
{

	int count;

	char name1_str[strlen(name1)];
	memset(name1_str,'0',strlen(name1));

	char name2_str[strlen(name2)];
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

