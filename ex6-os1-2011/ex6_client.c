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
#define MAX_MSG 30

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

	key_t 				key;
	int 				queue_id		=	0;
	double				pai_calculated	=	0;
	struct my_msgbuf 	my_msg;

	// If the user enter nesesery data corect:
	if(argc != 3)
	{
		incorect_param();						//	print error
		exit(EXIT_FAILURE);
	}

	queue_id 		= 	init_msg(atoi(argv[1]));//	init msg
		
	my_msg.mtype 	= 	atoi(argv[2]);			//put second param to msg type

	memset(my_msg.mtext,'\0',sizeof(my_msg.mtext));
	
	pai_calculated 	=	culcPai(atoi(argv[2]));	
	
	sprintf(my_msg.mtext, "%.10f\n",pai_calculated);

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

	double xVal,
		   yVal,
		   distance,
		   totalPoints = multiplier * 1000,
		   pointsIn = 0;

	int index;

	srand(time(NULL));

	for(index = 0; index < totalPoints; index ++)
	{
		xVal = (double) rand()/RAND_MAX;
		yVal = (double) rand()/RAND_MAX;

		distance = (xVal * xVal) + (yVal * yVal);
		distance = distance * distance;

		if(distance <= 1)
			pointsIn ++;

	}

	return (4 * (pointsIn / totalPoints));
}

//=============================================================================
//=============================================================================
//=============================================================================
