//                               Include section
//=============================================================================
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <math.h>

#define MAX_MSG_LEN 13


struct my_msgbuf
{
	long mtype;
	char mtext[MAX_MSG_LEN];
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
//	Function which start msg
int init_msg(const int ext_key);

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

	int 				queue_id		=	0;	// internal comunication key
	double				pai_calculated	=	0;  // pai value.
	struct my_msgbuf 	my_msg;					// transfer data structur.

	// If the user enter nesesery data corect:
	if(argc != 3)
	{
		incorect_param();						//	print error
		exit(EXIT_FAILURE);
	}

	queue_id 		= 	init_msg(atoi(argv[1]));//	init msg

	my_msg.mtype 	= 	atoi(argv[2]);			//put second param to msg type

	memset(my_msg.mtext,'\0',sizeof(my_msg.mtext));	// to be shur that clin str

	pai_calculated 	=	culcPai(atoi(argv[2])); // calc pai.

	sprintf(my_msg.mtext, "%.10f\n",pai_calculated); // Print pai.

	// Send messeg to server.
	if(msgsnd(queue_id, (struct msgbuf*)&my_msg, MAX_MSG_LEN, IPC_NOWAIT))
		errExit("msgsnd()failed\n");

	return(EXIT_SUCCESS);

}


//                             Function section
//=============================================================================

//=============================================================================
//	Function which start msg
int init_msg(const int ext_key)
{
	int 			queue_id = 0;		//			msg desc id
	key_t 			key;				//			ftok key

	if((key = ftok("/tmp", ext_key)) == -1)
		errExit("ftok()failed\n");		//			Print error and exit
	if((queue_id = msgget(key,0)) == -1)
		errExit("msgget()failed\n");	//			Print error and exit

	return(queue_id);					//			return msg desc id

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
	printf("1. queue_id\n");
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
