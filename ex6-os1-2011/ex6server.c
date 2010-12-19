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
#define MAX_MSG 3000



struct my_msgbuf
{
	long mtype;
	char mtext[MAX_MSG_LEN];
};

int quit = 0;


struct Node
{
	struct my_msgbuf msgStorge;
	struct Node *_next;
};



//                             Prototypes section
//=============================================================================








//------------------------------- Incorrect param------------------------------
//	print message of incorrect input parameters
void incorect_param();

void stopServer(int sig_num);

double stodoub(const char *str);

double calcAverage(struct Node *nod);

void printErorr(const char *msg);




struct Node *Allocate_Node()
{
	struct Node *temp = NULL;
	
	temp = malloc(sizeof(struct Node));
	
	if(temp == NULL)
		exit(EXIT_FAILURE);
	
	temp->_next = NULL;
	return(temp);
}

//                                Main section
//=============================================================================
int main(int argc, char *argv[])
{
	struct my_msgbuf msgStorge[MAX_MSG];
	struct Node *head = NULL;
	key_t key;
	struct Node *temp = NULL;
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

		if(head == NULL)
			head = Allocate_Node();
		else
		{
			temp = Allocate_Node();
			temp->_next = head;
			head = temp;
		
		}
		status = msgrcv(queue_id,(struct msgbuf*)&my_msg, MAX_MSG_LEN, allowed_type, IPC_NOWAIT);
		if(status > 0)
		{
			head->msgStorge = my_msg;
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
		pai = calcAverage(head);

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
double calcAverage(struct Node *nod)
{
	double average = 0;
	int index;
	long int divides = 0;
	struct Node *temp = NULL;

	temp = nod;
	for(index = 0; temp->_next !=NULL; index ++)
	{
		
		average += (temp->msgStorge.mtype) * (stodoub(temp->msgStorge.mtext));
		divides += temp->msgStorge.mtype;
		temp = temp->_next;
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
