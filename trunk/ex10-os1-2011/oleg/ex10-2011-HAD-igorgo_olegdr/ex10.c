/*        `';,.  Exercise No' 10 .,;'`
* ===========================================
* Writen by: Igor Govorov,  ID: 317362812,  LogIn: igorgo
*			 Oleg Ruchlis,  ID: 310140629,  LogIn: olegdr
*
* The program does multplication of matrix and a vector
* using threads in few diffrent manners.
*
* input: user gives the values for the vector and the matrix
*		 and choses which way to handle the threads.
*		 all through a simple menu with values 1 to 5.
* output: the multiplyingresult of the matrix and the vector.
*		  also contains deails on the operating threads.
*/
// --->> Include Section <<---
#include <stdio.h>	// Standart I/O functions
#include <stdlib.h>	// For EXIT_FAILURE / EXIT_SUCCESS.
#include <pthread.h>// Thread handling functions

// --->> Define Section <<----
#define INITMAT 1	// Value of users's choice for matrix init.
#define INITVEC 2	// Value of users's choice for vector init.
#define TAPJOIN 3	// Value of users's choice for thread joining.
#define TAPDETACH 4 // Value of users's choice for thread detaching.
#define TAPKEY 5	// Value of users's choice for specified data per thread.
#define DEFSIZE 3	// Default matrix / vector size.
#define MAX_STR_SIZE 6	// Maximal input string per number.

// --->> Prototype Section <<---

// Data structure for passing a pointer to thread.
struct dataBase{
	int _mat[DEFSIZE][DEFSIZE];	// the recieved matrix.
	int _vec[DEFSIZE];			// the recived vector.
	int _pos;					// position to work on for the current thread.
};

// This function prints the user's menu and performs an input check.
// recieves: input from stdin.
// returns:	 The numeral choice of the user.		
int userMenu();

// This function initializes the vector array.
// recieves: vector array.
// returns:	 the array with user's values.
void initVec(int arr[]);

// This function performs matrix and vector multiplying with the help
// of 3 diffrent threads that will be joined
// recieves: pointer to the database.
// returns:	 Prints the multiplying result.
void mulJoin3(struct dataBase* data);
	
// This function performs matrix and vector multiplying with the help
// of 3 diffrent threads that will be detached.
// recieves: pointer to the database.
// returns:	 Prints the multiplying result.
void mulDetach4(struct dataBase* data);

// This function performs matrix and vector multiplying with the help
// of 3 diffrent threads that will use specified data method.
// recieves: pointer to the database.
// returns:	 Prints the multiplying result.
void mulKey5(struct dataBase* data);
	
// This function will be used by the threads created in mulJoin3. makes the
// multiplying calculation.
// recieves: pointer to the database.
// returns:	 pointer to the calculated value.
void* threadMulFunc3(void* args);

// This function will be used by the threads created in mulDetach4. makes the
// multiplying calculation.
// recieves: pointer to the database.
// returns:	 prints the calculated value.
void* threadMulFunc4(void* args);

// This function will be used by the threads created in mulKey5. makes the
// multiplying calculation.
// recieves: pointer to the database.
// returns:	 nothing. calls the printRes function.
void* threadMulFunc5(void* args);

// This function prints the thread id for each thread functions.
// recieves: pointer to threads id (unsigned int).
// returns:	 The numeral choice of the user.
void printMsg(void* tid);

// This function initializes the key for specific data.
// recieves: Nothing.
// returns:	 Nothing.
void init_key();

// This function prints the threads calculation result, using the key
// to access threads specific data.
// recieves: the key of the thread.
// returns:	 prints the calculation result.
void printRes(pthread_key_t key);

// This function is freeing the memory used by the thread. part of the 
// destructor (cleanup) functions.
// recieves: pointer the allocated memory.
// returns:	 Nothing.
void freeMalloc(void* point);

// --->> Globals Section <<---
pthread_key_t key[DEFSIZE];
pthread_once_t threads_init[DEFSIZE];
// --->> Main Section <<----
int main()
{
	// the main database.
	struct dataBase db;
	
	// will contains user's choice in the menu.
	int uChoice;
	
	// index for loop purposes.
	int i;
	
	// infinite loop, exit only through threads proccess (3-5).
	while(1)
	{
		// prints the menu and recieves user's choice.
		uChoice = userMenu();
	
		// checking what did the user want.
		switch(uChoice)
		{
			// option number 1 - matrix init.
			case INITMAT:
				// initializing each vector of the matrix.
				for(i = 0 ; i < DEFSIZE ; i++)
					initVec(db._mat[i]);
				break;
			
			// option number 2 - vector init.
			case INITVEC:
				initVec(db._vec);
				break;
			
			// option number 3 - as described on mulJoin3.
			case TAPJOIN:
				mulJoin3(&db);
				break;
			
			// option number 4 - as described on mulDetach4.
			case TAPDETACH:
				mulDetach4(&db);
				break;
			
			// option number 5 - as described on mulKey5.
			case TAPKEY:
				mulKey5(&db);
				break;
		}
	}
	return(EXIT_SUCCESS);
}

//------------------------------------------------------------------------------

int userMenu()
{
	char choice = '0';

	// while choice variable haven't recieved useful value.
	while(choice < '1' || choice > '5')
	{
		// menu print:
		puts("What would you like to do:");
		puts("1 - Init the 3x3 matrix.");
		puts("2 - Init the 1x3 vector.");
		puts("3 - Thread and print - join.");
		puts("4 - Thread and print - detach.");
		puts("5 - Thread and print - key.");
		
		// recieving user's choice.
		choice = getc(stdin);
		
		// input check
		if(choice < '1' || choice > '5')
			puts("Please follow the instructions.");
	}
	
		
	// returning the choice (as an int).
	return(atoi(&choice));
}

//------------------------------------------------------------------------------

void initVec(int arr[])
{
	// indexes for input strings.
	int i, j = 0;
	
	// the current recieved char.
	char temp;

	// the current recieved string.
	char str[MAX_STR_SIZE];
	
	// recieving DEFSIZE values.
	for(i = 0 ; i < DEFSIZE ; i++)
	{
		// skipping blank spaces
		while((temp = getc(stdin)) == ' ' || temp == '\n');
		
		// while didn't reach the end of the string.
		while(temp != ' ' &&
			  temp != '\n' &&
			  j < MAX_STR_SIZE-1)
		{
			str[j] = temp;
			j++;
			temp = getc(stdin);
		}
		
		// null termintaed string
		str[j] = '\0';		
		
		// preparing for another loop.
		j=0;
		
		// converting into int.
		arr[i] = atoi(str);
	}
}

//------------------------------------------------------------------------------
void mulJoin3(struct dataBase* data)
{
	// result vector.
	int res[DEFSIZE],
	    // index.
	    i = 0;
	
	// value recieved from the thread
	int* retVal;

	// thread ids array.
	pthread_t tc[DEFSIZE];
	
	// starting from the first vector of the matrix
	data->_pos = 0;
	
	// making DEFSIZE threads
	for(i = 0 ; i < DEFSIZE ; i++)
	{
		// creating the threads + check.
		if ((pthread_create(&tc[i], NULL, threadMulFunc3, (void *)data)) != 0)
		{
			perror("pthread_create() had failed!");
			exit(EXIT_FAILURE);
		}
		
		// attaching the threads back and recieving value.
		if((pthread_join(tc[i], (void *)&retVal)) < 0)
			fputs("pthread_join() had failed", stderr);
		
		// saving the value.
		res[i] = *retVal;
		
		// freeing memory.
		free(retVal);
		
		// advancing to the next vector of the matrix.
		data->_pos++;
	}
	
	puts("The result is:");
	for( i = 0 ; i < DEFSIZE ; i++)		
		printf("%d ", res[i]);

	puts("\nGoodbye!");
	
	exit(EXIT_SUCCESS);
}

//------------------------------------------------------------------------------

void* threadMulFunc3(void* args)
{
	// setting the cancel values.
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	
	// sending thread's pid to cleanup (post mortum print).
	pthread_t me = pthread_self();
	pthread_cleanup_push(printMsg, (void *)&me);

	// index.
	int i;
	
	// casting the recieved data.
	struct dataBase* data = (struct dataBase*)args;
	
	// allocating memory for the return value.
	int *ret_val = (int *)malloc(sizeof(int)); 
	
	if(ret_val == NULL)
	{
		fprintf(stderr, "Allocation failure! \n");
		exit(EXIT_SUCCESS);
	}
	
	*ret_val = 0;
	
	// calculation:
	for (i = 0 ; i < DEFSIZE ; i++)
		*ret_val += data->_mat[data->_pos][i] * data->_vec[i];
	
	// exiting with return value.
	pthread_exit((void *)ret_val);
	
	// performing the cleanup (pid print).	
	pthread_cleanup_pop(0);
}

//------------------------------------------------------------------------------

void mulDetach4(struct dataBase* data)
{
	int i=0;
	
	pthread_t tc;
	
	// making a DEFSIZE array of databases, each thread will recieve one
	// of his own (avoiding race condition).	
	struct dataBase dataArr[DEFSIZE];
	
	for(i = 0 ; i < DEFSIZE ; i++)
	{
		dataArr[i] = *data;
		dataArr[i]._pos = i;
	}		
	
	puts("Starting calcualtion:\n");
	
	for(i = 0 ; i < DEFSIZE ; i++)
	{
		// thread creation + check.
		if((pthread_create(&tc, NULL, threadMulFunc4, (void *)&dataArr[i]))!= 0)
		{
			perror("pthread_create() had failed!");
			exit(EXIT_FAILURE);
		}
		
		// detaching the proccess.
		pthread_detach(tc); 
		
		// trying to attach back (will fail).
		if((pthread_join(tc, NULL)))
			fprintf(stderr,"pthread_join on %u had failed\n",(unsigned int)tc);
	}
	
	pthread_exit(EXIT_SUCCESS);
}

//------------------------------------------------------------------------------

void* threadMulFunc4(void* args)
{
	// setting the cancel values.
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	
	// sending thread's pid to cleanup (post mortum print).
	pthread_t me = pthread_self();
	pthread_cleanup_push(printMsg, (void *)&me);
	
	int i,			// index  for the loop.
		sum = 0;	// calculated sum.
	
	// casting the database.
	struct dataBase* data = (struct dataBase*)args;
	
	// calculating.
	for (i = 0 ; i < DEFSIZE ; i++)
		sum += data->_mat[data->_pos][i] * data->_vec[i];

	printf("Thread %u claculated: %i.\n", (unsigned int)me, sum);
	
	pthread_exit(EXIT_SUCCESS);	
	pthread_cleanup_pop(0);
}


//------------------------------------------------------------------------------

void mulKey5(struct dataBase* data)
{
	int i=0;	// loop index.
	
	pthread_t tc;	// threads id.
	
	// defining a set of databases. a copy for each thread.
	struct dataBase dataArr[DEFSIZE];
	
	// making the copies.
	for(i = 0 ; i < DEFSIZE ; i++)
	{
		dataArr[i] = *data;
		dataArr[i]._pos = i;
		threads_init[i] = PTHREAD_ONCE_INIT;
	}		
	
	puts("Starting calcualtion:\n");
	
	for(i = 0 ; i < DEFSIZE ; i++)
	{
		// thread creation + check.
		if ((pthread_create(&tc, NULL, threadMulFunc5, (void *)&dataArr[i]))!=0)
		{
			perror("pthread_create() had failed!");
			exit(EXIT_FAILURE);
		}
		
		// detaching the thread
		pthread_detach(tc); 
		
		// trying to attach back (will fail).
		if((pthread_join(tc, NULL)))
			fprintf(stderr,"pthread_join on %u had failed\n",(unsigned int)tc);
	}
	
	pthread_exit(EXIT_SUCCESS);
}

//------------------------------------------------------------------------------
void* threadMulFunc5(void* args)
{
	// setting the cancel values.
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	
	// sending thread's pid to cleanup (post mortum print).
	pthread_t me = pthread_self();
	pthread_cleanup_push(printMsg, (void *)&me);
	
	int i;	// loop index.
		
	
	// allocating memory for the return value.
	int *sum = (int*)malloc(sizeof(int));
	
	// casting the recieved database.
	struct dataBase* data = (struct dataBase*)args;
	
	// initializing keys (happens only once!).
	pthread_once(&threads_init[data->_pos], init_key);
	
	// allocation check.
	if(sum == NULL)
	{
		fputs("malloc had failed.", stderr);
		exit(EXIT_FAILURE);
	}
	
	// making sure the memory will be freed after death.
	pthread_cleanup_push(freeMalloc, sum);
	
	// calculating
	for (i = 0 ; i < DEFSIZE ; i++)
		*sum += data->_mat[data->_pos][i] * data->_vec[i];
	
	// setting the specific data + check.
	if(pthread_setspecific(key[data->_pos], sum))
	{
		fputs("pthread_setspecific() had failed.", stderr);
		exit(EXIT_FAILURE);
	}
	
	// printing the resault (via the key).
	printRes(key[data->_pos]);
	
	// exit + cleanup.
	pthread_exit(EXIT_SUCCESS);	
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
}

//------------------------------------------------------------------------------

void printMsg(void* tid)
{
	unsigned int* id = (unsigned int*)tid;
	printf("Pthread %u finished.\n", *id);
}

//------------------------------------------------------------------------------
void init_key()
{
	int i,
		rc;
	for(i = 0 ; i < DEFSIZE ; i++)
	{
		rc = pthread_key_create(&key[i], NULL);
		
		if(rc)
		{
			fputs("Pthread_key_create() had failed.", stderr);
			exit(EXIT_FAILURE);
		}
	}
}

//------------------------------------------------------------------------------
void printRes(pthread_key_t key)
{
	int sum = *((int *)pthread_getspecific(key));
	printf("The number is: %i.\n",sum);
}

//------------------------------------------------------------------------------

void freeMalloc(void* point)
{
	free((int *)point);
}
