// ex10


//                               Include section
//=============================================================================
#include <stdio.h>
#include <stdlib.h> 	// for EXIT_SUCCESS
#include <ctype.h>		// for fuction isdigit
#include <pthread.h>	// for thread using
#include <unistd.h>		// for function sleep







#define MAX_ROW 3	// difine number of max rows
#define MAX_COL 3	// difine number of max cols


//							Structs and Globals
//=============================================================================

// data base to send to tread to wark on it
struct db{
	int _matrix[MAX_ROW][MAX_COL];	// matrix strutur
	int _vector[MAX_COL];			// vector structur
	int _mat_row;					// on wich row of matrix need to work
};



pthread_key_t key;
pthread_once_t threads_init;



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
//	Function which multiplying matrix by vector, using 3 tread and the treads
//	using return value option (join).
//  get pointer to data base that includ matrix and vector.
void culc_vec_join(struct db *data_base);

//=============================================================================
//	Function for ptread that return value, which multiplying two (1x3) vectors
//  get pointer to data base that includ matrix and vector.
//  return of multiplying to the main tread.
void *thr_join(void *arg);

//=============================================================================
//	Function which multiplying matrix by vector, using 3 tread and the treads
//	print them self the risult of multiplying.
//  get pointer to data base that includ matrix and vector.
void culc_vec_detach(struct db *data_base);

//=============================================================================
//	Function for ptread that dose'nt return value, which multiplying two (1x3)
//  vectors and print the risult strait to the std output.
//  get pointer to data base that includ matrix and vector.
void *thr_detach(void *arg);

//=============================================================================
//	Function which multiplying matrix by vector, using 3 tread
//	print them self the risult of multiplying and the using pthred key to save
//	thire results
//  get pointer to data base that includ matrix and vector.
void culc_vec_key(struct db *data_base);

//=============================================================================
//	Function for ptread that dose'nt return value, which multiplying two (1x3)
//  vectors and print the risult strait to the std output. the result of each
//	thread saved at oune global vairibal for each thread.
//  get pointer to data base that includ matrix and vector.
void *thr_key(void *arg);









//=============================================================================
//	Function which
//  get
void cleanup_msg(void* id);

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

//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(char *msg);

//=============================================================================
//	Function which init key memoery
void init_key();

//=============================================================================
//	Function which free allocated memory.
void free_alloc_mem(void* mem);

//=============================================================================
//	Function which print specific thread result of multiplying vectors.
void print_mul_result();





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

	while(!exit)					// Loop untill the user will want to exit
	{
		print_menu();				//	print indication menu

		input = get_input_int();	// get chois of of manu from user

		switch(input)
		{
					// fill matrix with values from user
			case 1:	fill_matrix(data_base._matrix);

					// Print the obtained matrix
					print_matrix(data_base._matrix);
					break;

					// fill vector with values from user
			case 2:	fill_vector(data_base._vector);

					// Print the obtained vector
					print_vector(data_base._vector);
					break;

					// calculate multiplying of matrix by vector and print the
					// resut by main thread
			case 3:	culc_vec_join(&data_base);
					break;

					// calculate multiplying of matrix by vector - the result
					// will print by the threads.
			case 4:	culc_vec_detach(&data_base);
					break;

					// calculate multiplying of matrix by vector - the result
					// will print by the threads. and each thread save it data
					// at it oun global virebal.
			case 5:	culc_vec_key(&data_base);
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
//	Function which multiplying matrix by vector, using 3 tread and the treads
//	using return value option (join).
//  get pointer to data base that includ matrix and vector.
void culc_vec_join(struct db *data_base)
{
	int r_vec[MAX_COL]; 		// result vector

	int *ret_val = NULL;		// single multiply result from tread

	int index = 0;		 		// for loop

	pthread_t t_vec[MAX_COL];	//  treads id's

	for(index = 0; index < MAX_COL; index++)
	{
		data_base->_mat_row = index;	// set wich matrix row will be multiply

		// if tread creation faild - print error ,leav the program.
		if ((pthread_create(&t_vec[index], NULL, thr_join,
			(void *)data_base)) != 0)
			errExit("pthread_create()failed\n");

		// if waiting for current tread failed - print error ,leav the program.
		if((pthread_join(t_vec[index], (void *)&ret_val)) != 0)
			errExit("pthread_join()failed\n");

			//fputs("pthread_join()failed", stderr);
			//exit(EXIT_FAILURE);

		r_vec[index] = *ret_val;	// get multipy result from current tread.
		free(ret_val);				// free allocated memory.
	}
	// print multiply result
	fprintf(stdout,"After multiplying calculation, ");
	print_vector(r_vec); // Print the obtained (multiplying result) vector

	fprintf(stdout,"Bye Bye\n");

	exit(EXIT_SUCCESS);
}

//=============================================================================
//	Function for ptread that return value, which multiplying two (1x3) vectors
//  get pointer to data base that includ matrix and vector.
//  return of multiplying to the main tread.
void *thr_join(void *arg)
{
	int index;
	struct db* data_base = (struct db*)arg;		// get access to data base
	int *ret_val = NULL;						// vaireble for returning data

	// set tread cancelation mod.
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

	pthread_t id = pthread_self();					// get current tread id
	pthread_cleanup_push(cleanup_msg, (void *)&id);	// set cleanup of thread

	// allocate memory for returning of multilying result. -if fail print error
	if((ret_val = (int *)malloc(sizeof(int))) == NULL)
		errExit("malloc()failed\n");

	(*ret_val) = 0;

	// calculation of multiplying:
	for (index = 0 ; index < MAX_COL ; index++)
		(*ret_val) += data_base->_matrix[data_base->_mat_row][index] *
					  data_base->_vector[index];

	pthread_exit((void *)ret_val);	// set thread to exit with return value

	// activate thread distructor
	pthread_cleanup_pop(0);
}

//=============================================================================
//	Function which multiplying matrix by vector, using 3 tread and the treads
//	print them self the risult of multiplying.
//  get pointer to data base that includ matrix and vector.
void culc_vec_detach(struct db *data_base)
{
	int index = 0;		 		// for loop

	pthread_t t_vec[MAX_COL];	// threads id's vector

	// print mesege abuote result
	fprintf(stdout, "After multiplying calculation, The obtained vector arguments is:\n");

	for(index = 0; index < MAX_COL; index++)
	{
		data_base->_mat_row = index;	// set wich matrix row will be multiply

		// if tread creation faild - print error ,leav the program.
		if ((pthread_create(&t_vec[index], NULL, thr_detach,
			(void *)data_base)) != 0)
			errExit("pthread_create()failed\n");

		// if detaching of current tread failed - print error ,leav the program.
		if ((pthread_detach(t_vec[index])) != 0)
			errExit("pthread_detach()failed\n");

		// if waiting for current tread failed - print error ,leav the program.
		// and that what will hapened because we detach the treads befor.
		if((pthread_join(t_vec[index], NULL)) != 0)
			fprintf(stdout, "pthread_join()failed\n");
	}
	sleep(5);		// for nice looking output (the thread was detached anyway)
	fprintf(stdout, "\n Bye Bye\n");	// for nice looking output

	pthread_exit(EXIT_SUCCESS);
}

//=============================================================================
//	Function for ptread that dose'nt return value, which multiplying two (1x3)
//  vectors and print the risult strait to the std output.
//  get pointer to data base that includ matrix and vector.
void *thr_detach(void *arg)
{
	int index;
	struct db* data_base = (struct db*)arg;		// get access to data base
	int result = 0;								//result of multiplying virebel

	// set tread cancelation mod.
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

	pthread_t id = pthread_self();					// get current tread id
	pthread_cleanup_push(cleanup_msg, (void *)&id);	// set cleanup of thread

	// calculation of multiplying:
	for (index = 0 ; index < MAX_COL ; index++)
		(result) += data_base->_matrix[data_base->_mat_row][index] *
					  data_base->_vector[index];

	// print the result
	fprintf(stdout,"\nvector argument that thread %u calculate is: %d\n",
					(unsigned int)id, result);

	pthread_exit(EXIT_SUCCESS);	// exit thread

	// for nice looking output - let pthread_join function error print first
	sleep(2);

	// activate thread distructor
	pthread_cleanup_pop(0);
}




//=============================================================================
//	Function which multiplying matrix by vector, using 3 tread
//	print them self the risult of multiplying and the using pthred key to save
//	thire results
//  get pointer to data base that includ matrix and vector.
void culc_vec_key(struct db *data_base)
{
	int index = 0;		 		// for loop

	pthread_t t_vec[MAX_COL];	// threads id's vector

	// print mesege abuote result
	fprintf(stdout, "After multiplying calculation, The obtained vector arguments is:\n");

	for(index = 0; index < MAX_COL; index++)
	{
		data_base->_mat_row = index;	// set wich matrix row will be multiply

		// if tread creation faild - print error ,leav the program.
		if ((pthread_create(&t_vec[index], NULL, thr_key,
			(void *)data_base)) != 0)
			errExit("pthread_create()failed\n");

		// if detaching of current tread failed - print error ,leav the program.
		if ((pthread_detach(t_vec[index])) != 0)
			errExit("pthread_detach()failed\n");

		// if waiting for current tread failed - print error ,leav the program.
		// and that what will hapened because we detach the treads befor.
		if((pthread_join(t_vec[index], NULL)) != 0)
			fprintf(stdout, "pthread_join()failed\n");
	}
	sleep(5);		// for nice looking output (the thread was detached anyway)
	fprintf(stdout, "\n Bye Bye\n");	// for nice looking output

	pthread_exit(EXIT_SUCCESS);
}

//=============================================================================
//	Function for ptread that dose'nt return value, which multiplying two (1x3)
//  vectors and print the risult strait to the std output. the result of each
//	thread saved at oune global vairibal for each thread.
//  get pointer to data base that includ matrix and vector.
void *thr_key(void *arg)
{
	int index;
	struct db* data_base = (struct db*)arg;		// get access to data base
	int *result = NULL;						//result of multiplying virebel

	// set tread cancelation mod.
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

	pthread_t id = pthread_self();					// get current tread id
	pthread_cleanup_push(cleanup_msg, (void *)&id);	// set cleanup of thread
	pthread_cleanup_push(free_alloc_mem, result);	// at the cleanup - free
													//allocated memory

	// allocate memory for saving of multilying result. -if fail print error
	if((result = (int *)malloc(sizeof(int))) == NULL)
		errExit("malloc()failed\n");

	// the key is created only once
	pthread_once(&threads_init, init_key);

	// calculation of multiplying:
	for (index = 0 ; index < MAX_COL ; index++)
		(*result) += data_base->_matrix[data_base->_mat_row][index] *
					  data_base->_vector[index];

	// Saving result for specific tread	- if faild exit and notify
	if(pthread_setspecific(key, result))
		errExit("pthread_setspecific()failed\n");

	// print the result through specific thread key.
	print_mul_result();

	pthread_exit(EXIT_SUCCESS);	// exit thread

	// for nice looking output - let pthread_join function error print first
	sleep(2);

	// activate thread distructor
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
}


//=============================================================================
//	Function which free allocated memory.
void free_alloc_mem(void* mem)
{
	free((int *)mem);	// free memory
}


//=============================================================================
//	Function which print specific thread result of multiplying vectors.
void print_mul_result()
{
	// in the other function we use result
	// the key enable the func to retrive the wanted data as opposed to another
	// data, storted using other keys


	int result = *((int *)pthread_getspecific(key));

	// print the result
	fprintf(stdout,"\nvector argument that thread %u, calculate is: %d\n",
					(unsigned int)pthread_self(), result);
}


//=============================================================================
//	Function which init key memoery
void init_key()
{
	//int index = 0, 	// var for loop.
	int temp_key = 0;	// numer of key

	//for(index = 0; index < MAX_COL; index++)	// loop key creation
	//{
		if((temp_key = pthread_key_create(&key, NULL)) != 0)
			errExit("Pthread_key_create()failed\n");
	//}
}

//=============================================================================
//	Function which
//  get
void cleanup_msg(void* id)
{

	fprintf(stdout,"\npthread_cleanup: ptread %u finished\n",
	*((unsigned int*)id));
	//unsigned int *tread_id = (unsigned int*)id;
	//fprintf(stdout,"pthread_cleanup: ptread %d finished\n", *tread_id);

}

//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(char *msg)
{
	perror(msg);						//	Print message
	exit(EXIT_FAILURE);					//	exit whith failure
}

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
