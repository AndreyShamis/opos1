/*
	This file are client which connected to server and send him
	the pi value are is calculeted in function culcPai by MonteCarlo method.

*/
//                               Include section
//=============================================================================
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <math.h>



#define MSGGET_FLAG		0600


//============================ STRUCTS ========================================
//	struct for retreidev messages
struct my_msgbuf
{
	short int mtype;
	double pai;
};

//                             Prototypes section
//=============================================================================

//=============================================================================
//	print message of incorrect input parameters
void incorect_param();
//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(char *msg);

//=============================================================================
//	Function which create shered memory
int init_msg(const int ext_key);

//=============================================================================
//	Function which get pointer to shered memory
struct my_msgbuf *get_ptr_to_shm(int shm_id);

//=============================================================================
//	function to calculate Pi
//	geting multiplayer
//	return claculated value
double culcPai(int multiplier);

///////////////////////////////////////////////////////////////////////////////
//                                Main section
//=============================================================================
int main(int argc, char **argv)
{

	int 		shm_id	= 	0,			// internal comunication key
				index = 0;				// for looping
	double		pai_calculated	=	0;  // pai value.
	struct my_msgbuf *shm_ptr = NULL;	// pointr to data base in shered memory

	// If the user enter nesesery data corect:
	if(argc != 3)
	{
		incorect_param();						//	print error
		exit(EXIT_FAILURE);
	}

	shm_id 		= 	init_msg(atoi(argv[1]));	//	init shered memory

	//memset(my_msg.mtext,'\0',sizeof(my_msg.mtext));	// to be shur that clin str

	pai_calculated 	=	culcPai(atoi(argv[2])); // calc pai.


	shm_ptr = get_ptr_to_shm(shm_id);

	if(!SHM_LOCKED)
		exit(EXIT_FAILURE);



	while(shm_ptr[index].mtype != 0) // finde next empty cell at shered memory
	{
		index ++;
		printf("%d\n",shm_ptr[index].mtype);
		printf("tralialia:\n");
	}


	shm_ptr[index].mtype = atoi(argv[2]);	//put second param to msg type
	shm_ptr[index].pai	 =  pai_calculated; // put pai to shered memory.

	return(EXIT_SUCCESS);

}


//                             Function section
//=============================================================================


//=============================================================================
//	Function which get pointer to shered memory
struct my_msgbuf *get_ptr_to_shm(int shm_id)
{
	struct my_msgbuf *shm_ptr;

	shm_ptr = (struct my_msgbuf*)shmat(shm_id, NULL, 0);
		if(!shm_ptr)
			errExit("shmatt()failed\n");

	return (shm_ptr);
}


//=============================================================================
//	Function which create shered memory
int init_msg(const int ext_key)
{
	int 			shm_id = 0;		//			shm desc id
	key_t 			key;				//			ftok key

	if((key = ftok("/tmp", ext_key)) == -1)
		errExit("ftok()failed\n");		//			Print error and exit
	if((shm_id = shmget(key, 0, MSGGET_FLAG)) == -1)
		errExit("shmget()failed\n");	//			Print error and exit

	return(shm_id);					//			return shm desc id

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
//	print message of incorrect input parameters
void incorect_param()
{
	printf("You need enter 2 parameters:\n");
	printf("2. time for timer\n");
	printf("2. multiplier for rand\n");

}

//=============================================================================
//	function to calculate Pi
//	geting multiplayer
//	return claculated value
double culcPai(int multiplier)
{

	double xVal,		// rndom x coordinate value.
		   yVal,		// rndom y coordinate value.
		   distance,	// distance of points.
		   totalPoints = multiplier * 1000,	// difine total points number.
		   pointsIn = 0;

	int index;	// for Looping.

	srand(time(NULL));	// init random.

	// Loop thrugh all random points, and calculate num of point in the circel.
	for(index = 0; index < totalPoints; index ++)
	{
		xVal = (double) rand()/RAND_MAX;
		yVal = (double) rand()/RAND_MAX;

		// alculate num of point in the circel
		distance = (xVal * xVal) + (yVal * yVal);
		distance = distance * distance;

		if(distance <= 1)
			pointsIn ++;

	}
	// return pai propabilety value.
	return (4 * (pointsIn / totalPoints));
}

//=============================================================================
//=============================================================================
//=============================================================================
