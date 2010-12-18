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

#define MAX_MSG_LEN 13
#define MAX_MSG 30



struct my_msgbuf
{
	long mtype;
	char mtext[MAX_MSG_LEN];
};

int quit = 0;




//                             Prototypes section
//=============================================================================








//------------------------------- Incorrect param------------------------------
//	print message of incorrect input parameters
void incorect_param();

void stopServer(int sig_num);

double stodoub(const char *str);

double calcAverage(struct my_msgbuf msgStorge[]);

void printErorr(const char *msg);






//                                Main section
//=============================================================================
int main(int argc, char *argv[])
{
	struct my_msgbuf msgStorge[MAX_MSG];

	key_t key;
	int queue_id;
	struct my_msgbuf my_msg;
	int status;
	long int allowed_type = 0;

	double pai;

	memset(msgStorge,0,sizeof(msgStorge));


	signal(SIGALRM, stopServer);
	signal(SIGINT, stopServer);


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
	if((queue_id = msgget(key,IPC_CREAT | IPC_EXCL | 0600)) == -1)
	{
		perror("msgget()failed");
		exit(EXIT_FAILURE);
	}


	//for(index = 0; index < argv[2] || stopServer; index++)


	int counter = 0;

	alarm(atoi(argv[2]));

	while(!quit)
	{



		status = msgrcv(queue_id,(struct msgbuf*)&my_msg, MAX_MSG_LEN, allowed_type, IPC_NOWAIT);
		if(status > 0)
		{
			msgStorge[counter] = my_msg;
			//puts(msgStorge[counter].mtext);																		//TEST
			//printf("mul = %ld\n", msgStorge[counter].mtype);													//TEST


			counter ++;
		}
		sleep(1);
	}

	if(msgctl(queue_id, IPC_RMID, NULL) == -1)
	{
		perror("msgctl()failed");
		exit(EXIT_FAILURE);
	}


	if(atoi(msgStorge[0].mtext))
	{
		pai = calcAverage(msgStorge);

		printf("pai = %.10f\n", pai);
	}
	return(EXIT_SUCCESS);
}


//                             Function section
//=============================================================================


// A function that
//-----------------------------------------------------------------------------
void stopServer(int sig_num)
{
	quit = 1;
}


// A function that
//-----------------------------------------------------------------------------
// Input:
// Return:
double calcAverage(struct my_msgbuf msgStorge[])
{
	double average = 0;
	int index;
	long int divides = 0;

	for(index = 0; msgStorge[index].mtype > 0; index ++)
	{
		average += (msgStorge[index].mtype) * (stodoub(msgStorge[index].mtext));
		divides += msgStorge[index].mtype;
	}

	if(divides)
	{
		average = average / divides;
		return average;
	}

	return (0);
}


//------------------------------- Incorrect param------------------------------
//	print message of incorrect input parameters
void incorect_param()
{
	printf("You need enter 2 parameters:\n");
	printf("1. queue_id\n");
	printf("2. time for timer\n");

}


// A function that
//-----------------------------------------------------------------------------
// Input:
// Return:
double stodoub(const char *str)
{

	double doub;
	sscanf (str,"%lf\n",&doub);
	//puts(str);											//TEST
	//printf("##### = %.10f\n", doub);											//TEST
	return doub;
}
