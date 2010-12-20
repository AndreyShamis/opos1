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

#define MSGGET_FLAG		IPC_CREAT | IPC_EXCL | 0600


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

double calcAverage(struct Node *nod);

void printErorr(const char *msg);

struct Node *Allocate_Node();

void errExit(char *msg);

void clear_memory(struct Node *head);

void print_result(struct Node *head);

struct Node *retreive_data(const int queue_id);

struct Node *getNextNode(struct Node *head);




//                                Main section
//=============================================================================
int main(int argc, char *argv[])
{
	key_t 	key;
	int 	queue_id;
	int ext_key	=	0;
	struct Node *head = NULL;


	
	signal(SIGALRM, stopServer);
	signal(SIGINT, stopServer);

	// If the user enter nesesery data corect:
	if(argc != 3)
	{
		incorect_param();						//	print error
		exit(EXIT_FAILURE);
	}
	ext_key = atoi(argv[1]);

	if((key = ftok("/tmp", ext_key)) == -1)
		errExit("ftok()failed\n");
	if((queue_id = msgget(key,MSGGET_FLAG)) == -1)
		errExit("msgget()failed\n");

	alarm(atoi(argv[2]));


	head = retreive_data(queue_id);
		
	print_result(head);

	clear_memory(head);

	return(EXIT_SUCCESS);

}


struct Node *retreive_data(const int queue_id)
{

	struct my_msgbuf 	my_msg;
	//struct my_msgbuf	msgStorge;
	int 				status;
	long int 			allowed_type = 0;
	struct Node 		*head = NULL;
	
	while(!quit)
	{
		//memset(my_msg.mtext , '\0' ,sizeof(my_msg.mtext));	
			
		status = msgrcv(queue_id,(struct msgbuf*)&my_msg, MAX_MSG_LEN, allowed_type, IPC_NOWAIT);
		if(status > 0)
		{
			head= getNextNode(head);
			//memset(head->msgStorge.mtext , '\0' ,sizeof(head->msgStorge.mtext));	
			//memset(msgStorge,0,sizeof(msgStorge));
			//memset((void *)&head->msgStorge,0,sizeof(head->msgStorge));
			//memset(msgStorge,0,sizeof(msgStorge));
			//msgStorge = my_msg;
			head->msgStorge = my_msg;
		}
		sleep(1);
	}

	if(msgctl(queue_id, IPC_RMID, NULL) == -1)
		errExit("msgctl()failed\n");	

	return(head);
}

struct Node *getNextNode(struct Node *head)
{
	struct Node *temp 	= 	NULL;

	if(head == NULL)
		head = Allocate_Node();
	else
	{
		temp = Allocate_Node();
		temp->_next = head;
		head = temp;		
	}
	
	return(head);
		
}

void print_result(struct Node *head)
{
	double 	pai	=	0;					//	pi variable

	if(head!= NULL)
	{
		pai = calcAverage(head);		//	get value of pi

		fprintf(stdout,"pai = %.10f\n", pai);	//
	}

}
//=============================================================================
//	function which allocate new cell 
//	return pointer to new cell
struct Node *Allocate_Node()
{
	struct Node *temp = NULL;
	
	temp = malloc(sizeof(struct Node));
	
	if(temp == NULL)
		errExit("Can not allocate memory.\n");
	
	temp->_next = NULL;
	
	return(temp);

}


//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

//=============================================================================
//	function wich clear the memory which was used
void clear_memory(struct Node *head)
{
	struct Node *temp = NULL;
	
	while(head != NULL)
	{
		temp = head->_next;
		free(head);
		head= temp;
	}
	
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
// Inpu-t:
// Return:
double calcAverage(struct Node *nod)
{
	double average = 0;
	int index = 0;
	long int divides = 0;
	struct Node *temp = NULL;

	temp = nod;
	for(index = 0; temp->_next !=NULL; index ++)
	{		
		average += temp->msgStorge.mtype * atof(temp->msgStorge.mtext);
		divides += temp->msgStorge.mtype;
		temp = temp->_next;
	}

	if(divides)
	{
		average = average / divides;
		return (average);
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

