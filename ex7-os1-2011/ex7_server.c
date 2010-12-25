/*

	Provide server for clients which calculated pi
	and send it to server.
	Server waiting X second.X mast be provided in argv-2.
*/

//                               Include section
//=============================================================================
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <signal.h>






#define MSGGET_FLAG		IPC_CREAT | IPC_EXCL | 0600

//=============================================================================
//                        Variable and struct section

int quit = 0;	//global variable to get exit status can be updated in handler

//============================ STRUCTS ========================================
//	struct for retreidev messages
struct my_msgbuf
{
	short int mtype;
	double mtext;
};

//=============================================================================
//								Prototypes
//=============================================================================
//	print message of incorrect input parameters
void incorect_param();

//=============================================================================
// A handler function
//	Updating gloabal to exit from program
void stopServer(int sig_num);

//=============================================================================
//	Function ti calculate Pi over all clients was geted
// Inpu-t:	pointer to the shered memory, data base size
// Return:	value of Pai
double calcAverage(struct my_msgbuf *data_base, int num_of_pais);

//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(char *msg);

//=============================================================================
//	function which print pi
void print_result(const double pai);

//=============================================================================
//	Function which create shered memory
int init_shm(const int ext_key, int shm_size);

//=============================================================================
//	Function which set signal handler
void setHandlers();

//=============================================================================
//	Function which colse shered memory
void close_shm(int shm_id);

//=============================================================================
//	Function which make dilay for witen to data at shered memory.
void wait_for_data(int *counter, int timer, int shm_id, int shm_size);

//=============================================================================
//	Function which get pointer to shered memory
int *get_ptr_to_shm(int shm_id);

//=============================================================================
//	Function which lock access to shered memory  ot the claents.
void lock_shm(int shm_id);



//*****************************************************************************
//*****************************************************************************
//*****************************************************************************


//=============================================================================
//	Main function
int main(int argc, char **argv)
{
	int 			shm_id	= 	0,			//	internal comunication key
	 				ext_key		=	0,		//	external comunication key
	 				shm_size	=	0;
	double 			pai_res		=	0;			//	pi variable

	int *counter = NULL;

	struct my_msgbuf *data_base = NULL;	// pointr to data base in shered memory

	// If the user enter nesesery data corect:
	if(argc != 4)
	{
		incorect_param();						//	print error
		exit(EXIT_FAILURE);
	}
	shm_size = atoi(argv[3]);					// shered memory size

	setHandlers();								//	set signal handlers

	ext_key 	= 	atoi(argv[1]);				//	get external key

	shm_id 	= 	init_shm(ext_key, shm_size);			//	init msg

	counter = get_ptr_to_shm(shm_id);			// get pointer to the shered memoey

	(*counter) = 0;						// reset counter

	// get pointer to the arr of structs at shered memory
	data_base = (struct my_msgbuf*)(counter + 1);

	// waiting for shered memory to be filled.
	wait_for_data(counter, atoi(argv[2]), shm_id, shm_size);


	pai_res = calcAverage(data_base, abs(*counter));		//	get value of pi

	if(pai_res)
		print_result(pai_res);						//	print reults

	close_shm(shm_id);						//	close shered memory

	return(EXIT_SUCCESS);

}

//=============================================================================
//	Function which lock access to shered memory  ot the claents.
void lock_shm(int shm_id)
{
	struct shmid_ds shm_desc;

	if(shmctl(shm_id, SHM_LOCK, &shm_desc) == -1)
		errExit("shmctl()failed\n");
}



//=============================================================================
//	Function which get pointer to shered memory
int *get_ptr_to_shm(int shm_id)
{
	int *temp;

	temp = (int*)shmat(shm_id, NULL, 0);
		if(!temp)
			errExit("shmatt()failed\n");

	return (temp);
}


//=============================================================================
//	Function which make dilay for witen to data at shered memory.
void wait_for_data(int *counter, int timer, int shm_id, int shm_size)
{
	alarm(timer);						//	set alarm

	while(!quit)
	{
		fprintf(stdout,"counter = %d\n", (*counter));

		if((*counter) ==  shm_size)
		{
			lock_shm(shm_id);
			(*counter) = (-1) * (*counter);
		}
	}
}

//=============================================================================
//	Function which colse shered memory
void close_shm(int shm_id)
{
	struct shmid_ds shm_desc;

	if(shmctl(shm_id, IPC_RMID, &shm_desc) == -1)
		errExit("shmctl()failed\n");	//			Print error and exit
}



//=============================================================================
//	Function which set signal handler
void setHandlers()
{
	signal(SIGALRM, stopServer);		//	set signal handler for Alarm
	signal(SIGINT, stopServer);			//	set signal handler for sigInt

}

//=============================================================================
//	Function which create shered memory
int init_shm(const int ext_key, int shm_size)
{
	int 			shm_id = 0;		//			shm desc id
	key_t 			key;				//			ftok key

	if((key = ftok("/tmp", ext_key)) == -1)
		errExit("ftok()failed\n");		//			Print error and exit
	if((shm_id = shmget(key, sizeof(int) + (sizeof(struct my_msgbuf) * shm_size), MSGGET_FLAG)) == -1)
		errExit("shmget()failed\n");	//			Print error and exit

	return(shm_id);					//			return shm desc id

}

//=============================================================================
//	function which print pi
void print_result(const double pai)
{
	fprintf(stdout,"pai = %.10f\n", pai);	//	print to stdout

}

//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(char *msg)
{
	perror(msg);					//	print err message
	exit(EXIT_FAILURE);				//	exit whith fail
}

//=============================================================================
//	Function ti calculate Pi over all clients was geted
// Inpu-t:	pointer to the shered memory, data base size
// Return:	value of Pai
double calcAverage(struct my_msgbuf *data_base, int num_of_pais)
{
	double 		average 	= 	0;		//	difine average of retreive pais.
	long int 	divides 	= 	0;		//	difine weight of calculation averag
	int 		index		=	0;		// for looping.
	fprintf(stdout,"num of pai = %d\n", num_of_pais);

	for(index = 0; index < num_of_pais; index++)
	{
		average += data_base[index].mtype * data_base[index].mtext;
		divides += data_base[index].mtype;

		fprintf(stdout,"##########pai = %.10f\n", data_base[index].mtext);
		//fprintf(stdout,"mtype = %d\n", data_base[index].mtype);

	}

	if(divides)							//	check if can devide
	{
		average = average / divides;	//	deviding
		return (average);				//	return value
	}

	return (0);							//	return other value

}


//=============================================================================
//	print message of incorrect input parameters
void incorect_param()
{
	printf("You need enter 3 parameters:\n");
	printf("1. shered memory id\n");
	printf("2. time for timer\n");
	printf("3. size of data base");

}

//=============================================================================
// A handler function
//	Updating gloabal to exit from program
void stopServer(int sig_num)
{
	quit = 1;							//	exit status from program

}

//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================

