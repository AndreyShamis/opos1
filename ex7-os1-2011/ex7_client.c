/*
	This file are client which connected to server and send him
	the pi value are is calculeted in function culcPai by MonteCarlo method.

*/
//                               Include section
//=============================================================================
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>

#define MSGGET_FLAG		0600

//============================ STRUCTS ========================================
//	struct for retreidev messages
struct my_msgbuf
{
	short int mtype;			//	type of msgbuf
	double pai;					//	pai value
};

//                             Prototypes section
//=============================================================================

//=============================================================================
//	print message of incorrect input parameters
void incorect_param();
//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(const char *msg);

//=============================================================================
//	Function which create shered memory
int init_msg(const int ext_key);

//=============================================================================
//	Function which get pointer to shered memory
int *get_ptr_to_shm(const int shm_id);

//=============================================================================
//	function to calculate Pi
//	geting multiplayer
//	return claculated value
double culcPai(const int multiplier);

//=============================================================================
//	function which witing data into shared memory
//	getting pointer to memory index in memory and value and type
//	return : nothing
void write_to_memory(struct my_msgbuf *shm_ptr,const int msg_type,
									const double pi_value,const int mem_index);

///////////////////////////////////////////////////////////////////////////////
//                                Main section
//=============================================================================
int main(int argc, char **argv)
{

	int 		shm_id			= 	0;		// internal comunication key
	double		pai_calculated	=	0;  	// pai value.
	int 		*counter  		= 	NULL;	// pointer to counter
	struct my_msgbuf *shm_ptr 	= 	NULL;	// pointer to memory

	// If the user enter nesesery data corect:
	if(argc != 3)
		incorect_param();						//	print error

	shm_id 		= init_msg(atoi(argv[1]));		//	init shered memory
	counter 	= get_ptr_to_shm(shm_id);		//	get pointer to counter
	shm_ptr 	= (struct my_msgbuf*)(counter + 1);//	calc pointer to mem

	if(!(*counter))								//	check if can write to mem
		errExit("Shered memory - Access blocked by server!\n");

	pai_calculated 	=	culcPai(atoi(argv[2])); // calc pai.
	
	(*counter) --;								//	decrease counter
	
	write_to_memory(shm_ptr,atoi(argv[2]),pai_calculated,(*counter));
	
	return(EXIT_SUCCESS);

}

//=============================================================================
//	function which witing data into shared memory
//	getting pointer to memory index in memory and value and type
//	return : nothing
void write_to_memory(struct my_msgbuf *shm_ptr,const int msg_type,
									const double pi_value,const int mem_index)
{
	shm_ptr[mem_index].mtype 	= msg_type; 	// sec param to msg type
	shm_ptr[mem_index].pai		= pi_value;		// put pi to shered memory
	
}

//=============================================================================
//	Function which get pointer to shered memory
int *get_ptr_to_shm(const int shm_id)
{
	int *temp;								//	variable be returned

	temp = (int*)shmat(shm_id, NULL, 0);	//	set pinter
		if(!temp)							//	check if temp not null
			errExit("shmatt()failed\n");

	return (temp);							//	return value

}

//=============================================================================
//	Function which create shered memory
int init_msg(const int ext_key)
{
	int 			shm_id = 0;			//			shm desc id
	key_t 			key;				//			ftok key

	if((key = ftok("/tmp", ext_key)) == -1)
		errExit("ftok()failed\n");		//			Print error and exit
	if((shm_id = shmget(key, 0, MSGGET_FLAG)) == -1)
		errExit("shmget()failed\n");	//			Print error and exit

	return(shm_id);						//			return shm desc id

}

//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(const char *msg)
{
	perror(msg);						//	Print message
	exit(EXIT_FAILURE);					//	exit whith failure

}

//=============================================================================
//	print message of incorrect input parameters
void incorect_param()
{
	errExit("You need enter 2 parameters:\n \
		\r1. Memory id \n \
		\r2. Multiplier for rand\n");

}

//=============================================================================
//	function to calculate Pi .geting multiplayer
//	return claculated value
double culcPai(const int multiplier)
{
	double xVal,							// rndom x coordinate value.
		   yVal,							// rndom y coordinate value.
		   distance,						// distance of points.
		   totalPoints 	= multiplier * 1000,// difine total points number.
		   pointsIn 	= 0;
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
