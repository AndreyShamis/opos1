#include "read.h"

// A function that read text file.
//-----------------------------------------------------------------------------
// Input: tabel of strings (type dubel pointer), counter of strings (type
// &char),
char **readLines(FILE *fRead,int *str_counter)
{
	char 	**temp	=	NULL, 				// Temp 2-array
			**dataDB=	NULL;				// 2-array be returned
	char 	data[MAX_STR_LEN];				// TEMP variable for string
	char 	*str	=	NULL;				// string-pointer
	int 	status	=	FILE_R;				// STATUS INPUT DATA
	int		data_len=	0;

	//	get data while file and console input not eof
	//	allocate memory for 2-array and for each string
	//	2-array size be reruned in str_counter pointer
	while(status != EOF_R)
	{

		//	------------ FILE READ BLOCK ---------------------------------
		if(status == FILE_R )				//	IF FILE NOT EOF
	 		if(!readLineFile(data,fRead))	//	READ FROM FILE TO data
				status = EOF_R; 			//	UNTIL NULL
		//	For give read to console change
		//	status = EOF_R; to status = CONSOLE_R;
		//	------------ END READ FILE BLOCK ----------------------------

		//	------------ CONSOLE READ BLOCK ------------------------------
		//if(status == CONSOLE_R )			// IF CONSOLE NOT EOF
		//	if(!readLineConsole(data))		// READ TO data FROM FILE
		//		status = EOF_R; 			// UNTIL NOT EOF
		//	------------ END READ CONSOLE BLOCK --------------------------
		if(status != EOF_R)
			data_len	=	strlen(data);

		//	have something in data variable
		//	and this somthings more than 2 charachters
		if(status != EOF_R && data_len>MIN_STR_LEN)
		{

			//	allocate memory for one string
			str = alloc_string(sizeof(char)*data_len+1);

			//	allocate memory for 2-array
			temp = alloc_cell((*str_counter)+1);

			//	rebuild temp from dataDB;
			copy_arr(temp,dataDB,*str_counter);

			//	clear previuos data-structure
			free(dataDB);

			//	set our data structure point to real structure
			dataDB = temp;

			// copy string which was geted to heap pointer
			strcpy(str,data);
			str[data_len] = '\0';

			// input string which was geted to our data structure
			dataDB[(*str_counter)] = str;

			//	inrement counter
			(*str_counter)++;
		}
	}

	return(dataDB);
}

//-------------- READ LINE FROM FILE ------------------------------------------
//	input 	pointer to string where be retuned string
//			file descriptor
//	---------------------------------------------------------------------------
//	return	0 - if input == NULL = EOF
//			1 - if input succeful
int readLineFile(char *data,FILE *fRead)
{
	//	try to get
	if(fgets(data,MAX_STR_LEN,fRead) != NULL)
		return(TRUE);						//	return succeful

	return(FALSE);							//	return fail

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

//-------------- READ LINE FROM CONSOLE ---------------------------------------
//	input 	pointer to string where be retuned string
//	---------------------------------------------------------------------------
//	return	0 - if input == NULL = EOF
//			1 - if input succeful
int readLineConsole(char *data)
{

	if(fgets(data,MAX_STR_LEN,stdin) != NULL)
		return(TRUE);						//	return succeful

	return(FALSE);							//	return fail

}

