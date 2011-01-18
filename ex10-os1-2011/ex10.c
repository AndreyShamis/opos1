// ex10


//                               Include section
//=============================================================================
#include <stdio.h>
#include <stdlib.h> 	// for EXIT_SUCCESS
#include <ctype.h>		// for fuction isdigit
#include <pthread.h>	// for thread using





#define MAX_ROW 3	// difine number of max rows
#define MAX_COL 3	// difine number of max cols




// data base to send to tread to wark on it
struct db{
	int _matrix[MAX_ROW][MAX_COL];	// matrix strutur
	int _vector[MAX_COL];			// vector structur
	int _mat_row;					// on wich row of matrix need to work
};


//=============================================================================
//								Prototypes
//=============================================================================

//=============================================================================
//	Function which printing user menu
void print_menu();

//=============================================================================
// A function that manage the program
void manage_program();

//=============================================================================
//	Function which get input from std input and return int value of input
//  the ufctiont check if the input is corect (is digits)
int get_input_int();

//=============================================================================
//	Function which fill matrix with value from user.
// 	The function get matrix (2D array).
void fill_matrix(int matrix[][MAX_COL]);

//=============================================================================
//	Function which fill vector with value from user.
// 	The function get vector (1D array).
void fill_vector(int vector[MAX_COL]);

//=============================================================================
//	Function which print obtained matrix.
// 	The function get matrix (2D array).
void print_matrix(int matrix[][MAX_COL]);

//=============================================================================
//	Function which print obtained vector.
// 	The function get vector (1D array).
void print_vector(int vector[MAX_COL]);







//*****************************************************************************
//*****************************************************************************
//*****************************************************************************


//=============================================================================
//	Main function
//=============================================================================
int main()
{
	manage_program();

	fprintf(stdout,"Bye Bye\n");

	return (EXIT_SUCCESS);
}

//                             Function section
//=============================================================================

//=============================================================================
// A function that manage the program
void manage_program()
{
	//int matrix[MAX_ROW][MAX_COL];	// matrix strutur
	//int vector[MAX_COL];			// vector structur

	struct db data_base;
	short int 	input	= 0;		// menu variable
	int		    exit 	= 0;		// exit difinder

	while (!exit)					// Loop untill the user will want to exit
	{
		print_menu();				//	print indication menu

		input = get_input_int();	// get chois of of manu from user

		switch(input)
		{
			case 1:	fill_matrix(data_base._matrix); // fill matrix with values from user
					print_matrix(data_base._matrix); // Print the obtained matrix
					break;

			case 2:	fill_vector(data_base._vector); // fill vector with values from user
					print_vector(data_base._vector); // Print the obtained vector
					break;

			//case 3:	culc_join(&matrix, &vector)	//
					break;

			//case 4:	culc_detach(&matrix, &vector)
					break;

			//case 5:	culc_key(&matrix, &vector)
					break;

			case 6: exit = 1;	// exit program
					break;
		}
	}
}

//=============================================================================
//	Function which get input from std input and return int value of input
//  the ufctiont check if the input is corect (is digits)
int get_input_int()
{
	int input;	// input value

	fscanf(stdin,"%d",&input);	//	get input.

	if(!isdigit(input + '0'))	// if wrong input - exit
	{
		//	notepy user about wrong input
		fprintf(stderr,"Incorrect input! \n \
				\rYou should enter only digits\n");


		exit(EXIT_FAILURE);
	}
	return input;	// return input
}

//=============================================================================
//	Function which fill matrix with value from user.
// 	The function get matrix (2D array).
void fill_matrix(int matrix[][MAX_COL])
{
	short int index_row = 0;
	short int index_col = 0;

	fprintf(stdout,"Please enter 9 values to fill the matrix cells \n");

	// Loop through matrix and fill the cells with values from user.
	for(index_row = 0; index_row < MAX_ROW; index_row ++)
		for(index_col = 0; index_col < MAX_COL; index_col ++)
			matrix[index_row][index_col] = get_input_int();

}


//=============================================================================
//	Function which fill vector with value from user.
// 	The function get vector (1D array).
void fill_vector(int vector[MAX_COL])
{
	short int index_col = 0;

	fprintf(stdout,"Please enter 3 values to fill the vector cells\n");

	// Loop through vector and fill the cells with values from user.
	for(index_col = 0; index_col < MAX_COL; index_col ++)
		vector[index_col] = get_input_int();
}

//=============================================================================
//	Function which print obtained matrix.
// 	The function get matrix (2D array).
void print_matrix(int matrix[][MAX_COL])
{
	short int index_row = 0;
	short int index_col = 0;

	fprintf(stdout,"The obtained matrix is:\n");	// tell user

	// Loop through matrix cells and print cells values.
	for(index_row = 0; index_row < MAX_ROW; index_row ++)
	{
		for(index_col = 0; index_col < MAX_COL; index_col ++)
			fprintf(stdout,"%d ", matrix[index_row][index_col]);

		fprintf(stdout,"\n");
	}

}

//=============================================================================
//	Function which print obtained vector.
// 	The function get vector (1D array).
void print_vector(int vector[MAX_COL])
{
	short int index_col = 0;

	fprintf(stdout,"The obtained vector is:\n"); // tell user

	// Loop through vectorcells and print cells values.
	for(index_col = 0; index_col < MAX_COL; index_col ++)
		fprintf(stdout,"%d ", vector[index_col]);

	fprintf(stdout,"\n");
}

//=============================================================================
//	Function which
//void culc_join(int &matrix, &vector)

















//=============================================================================
//	Function which printing user menu
void print_menu()
{
	fprintf(stdout,"What would you like to do:\n \
	\t# 1 - Init the 3x3 matrix. \n \
	\t# 2 - Init the 1x3 vector. \n \
	\t# 3 - Thread and print - join. \n \
	\t# 4 - Thread and print - detach. \n \
	\t# 5 - Thread and print - key. \n \
	\t# 6 - exit the program \n");

}
