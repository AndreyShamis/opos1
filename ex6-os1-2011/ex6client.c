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

#define MAX_MSG_LEN 11
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

void doubtostr(char *str, const double num);







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

	//pai = culcPai(atoi(argv[2]));

	my_msg.mtype = atoi(argv[2]);



	 doubtostr(my_msg.mtext, culcPai(atoi(argv[2])));





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
	printf("2. multiplier for rand");

}


double culcPai(int multiplier)
{
	srand(time(NULL));
	double xVal,
		   yVal,
		   distance,
		   totalPoints = multiplier * 1000000,
		   pointsIn = 0;

	int index;


	for(index = 0; index < totalPoints; index ++)
	{
		xVal = (double) rand()/RAND_MAX;
		yVal = (double) rand()/RAND_MAX;

		distance = (xVal * xVal) + (yVal * yVal);

		//printf("distance = %lf\n",distance);										//TEST

		//distance = sqrt(456);
		distance = sqrt(distance);

		printf("distance = %lf\n",distance);										//TEST

		if(distance <= 1)
		{
			//printf("LALAAALLALALALALALLALALALALALLALA\n");					//TEST
			pointsIn ++;
		}
	}
	printf("pai777 = %lf\n", (4 * (pointsIn / totalPoints)));				//TEST

	return (4 * (pointsIn / totalPoints));
}


// A function that
//-----------------------------------------------------------------------------
// Input:
// Return:
void doubtostr(char *str, const double num)
{
	sprintf(str, "%lf", num);

	//printf("pai = %lf\n", num);										//TEST

	puts(str);														//TEST

}

/*
// A function that
//-----------------------------------------------------------------------------
// Input:
// Return:
char* doubtostr(const double num)
{
	int index, 		//	counter
		complet;



	char chr[MAX_MSG_LEN];

	memset(chr,0,sizeof(chr));

	char remainder[MAX_MSG_LEN-2];
	double doub = num;

	complet = (int)doub

	chr[0] = (char)complet + '0';
	chr[1] = '.';

	for(index = 2; index <= MAX_MSG_LEN -2; index ++)

		chr[index] = (int)doub + '0';

		remainder[index-2] = str[index];

	doub += (atoi(remainder) / MAX_MSG_LEN -1);



	return(doub);

}

*/








