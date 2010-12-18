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

#define MAX_MSG_LEN 11
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




	alarm(atoi(argv[2]));

	while(!quit)
	{
		int counter = 0;


		status = msgrcv(queue_id,(struct msgbuf*)&my_msg, MAX_MSG_LEN, allowed_type, IPC_NOWAIT);
		if(status > 0)
		{
			msgStorge[counter] = my_msg;
			puts(msgStorge[counter].mtext);														//TEST

			counter ++;
		}
		sleep(1);
	}

	if(msgctl(queue_id,IPC_RMID,NULL) == -1)
	{
		perror("msgctl()failed");
		exit(EXIT_FAILURE);
	}


	if(atoi(msgStorge[0].mtext))
	{
		pai = calcAverage(msgStorge);

		printf("pai = %lf\n", pai);
		//puts(msgStorge[0].mtext);
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

	for(index = 0; !stodoub((char *)msgStorge[index].mtext); index ++)

		average += msgStorge[index].mtype * stodoub((char *)msgStorge[index].mtext);

	if(!average)
		average = average / index;

		return average;

	return (0);
}


//------------------------------- Incorrect param------------------------------
//	print message of incorrect input parameters
void incorect_param()
{
	printf("You need enter 2 parameters:\n");
	printf("1. queue_id\n");
	printf("2. time for timer");

}


// A function that
//-----------------------------------------------------------------------------
// Input:
// Return:
double stodoub(const char *str)
{
	int index,		//	counter
		len		=	0;		//	lentgh of string geted
	char remainder[MAX_MSG_LEN-2];
	double doub = str[0] - '0';



	len = strlen(str);		//	get lentgh of string


	for(index = 2; index <= len; index ++)

		remainder[index-2] = str[index];

	doub += (atoi(remainder) / MAX_MSG_LEN -1);

	return(doub);

}

