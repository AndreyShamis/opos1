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

//------------------------------- Incorrect param------------------------------
//	print message of incorrect input parameters
void incorect_param();

double culcPai(int multiplier);

//                                Main section
//=============================================================================
int main(int argc, char *argv[])
{

	key_t key;
	int queue_id;
	struct my_msgbuf my_msg;

	//double pai;

	// If the user enter nesesery data corect:
	if(argc != 3)
	{
		incorect_param();						//	print error
		exit(EXIT_FAILURE);
	}

	if((key = ftok("/tmp", atoi(argv[1]))) == -1)
	{
		perror("ftok()failed");
		exit(EXIT_FAILURE);
	}

	if((queue_id = msgget(key,0)) == -1)
	{
		perror("msgget()failed");
		exit(EXIT_FAILURE);
	}
	my_msg.mtype = atoi(argv[2]);



	 //doubtostr(my_msg.mtext, culcPai(atoi(argv[2])));

	 sprintf(my_msg.mtext, "%.10f\n", culcPai(atoi(argv[2])));

	if(msgsnd(queue_id, (struct msgbuf*)&my_msg, MAX_MSG_LEN, IPC_NOWAIT))
	{
		perror("msgsnd()failed");
		exit(EXIT_FAILURE);
	}



	return(EXIT_SUCCESS);
}


//                             Function section
//=============================================================================






//------------------------------- Incorrect param------------------------------
//	print message of incorrect input parameters
void incorect_param()
{
	printf("You need enter 2 parameters:\n");
	printf("1. queue_id\n");
	printf("2. multiplier for rand\n");

}


double culcPai(int multiplier)
{
	srand(time(NULL));
	double xVal,
		   yVal,
		   distance,
		   totalPoints = multiplier * 1000,
		   pointsIn = 0;

	int index;


	for(index = 0; index < totalPoints; index ++)
	{
		xVal = (double) rand()/RAND_MAX;
		yVal = (double) rand()/RAND_MAX;

		distance = (xVal * xVal) + (yVal * yVal);

		//printf("distance = %lf\n",distance);										//TEST

		//distance = sqrt(456);
		//distance = sqrt(distance);												//TODO
		distance = distance * distance;

		//printf("distance = %lf\n", distance);										//TEST

		if(distance <= 1)
		{
			pointsIn ++;
		}
	}
	//printf("pai777 = %.10f\n", (4 * (pointsIn / totalPoints)));				//TEST##############333

	return (4 * (pointsIn / totalPoints));
}


/*
void printErorr(const *char msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}




*/

