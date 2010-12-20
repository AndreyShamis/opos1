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

#define MSGGET_FLAG		IPC_CREAT | IPC_EXCL | 0600

//=============================================================================
//                        Variable and struct section

int quit = 0;	//global variable to get exit status can be updated in handler

//============================ STRUCTS ========================================
//	struct for retreidev messages
struct my_msgbuf
{
	long mtype;
	char mtext[MAX_MSG_LEN];
};

//	struct to save the list of nodes
struct Node
{
	struct my_msgbuf msgStorge;		//	struct my_msgbuf 
	struct Node *_next;				//	Pointer to next Node in list
};
//=============================================================================
//								Prototypes
//=============================================================================
//	print message of incorrect input parameters
void incorect_param();

//=============================================================================
// A handler function
//	Updating gloabal to exit from program
void stopServer(int sig_num);

//=============================================================================
//	Function ti calculate Pi over all clients was geted
// Inpu-t:	data geted by server in list
// Return:	value of PI
double calcAverage(struct Node *nod);

//=============================================================================
//	function which allocate new cell 
//	return pointer to new cell
struct Node *Allocate_Node();

//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(char *msg);

//=============================================================================
//	function wich clear the memory which was used
void clear_memory(struct Node *head);

//=============================================================================
//	function which print pi
void print_result(const double pai);

//=============================================================================
//	Function which retreive data and insert to list
//	Get the message queue_id
//	Return List
struct Node *retreive_data(const int queue_id);

//=============================================================================
//	Function which manipulate whith list
//	For insert every new node to head of list
//	Return manipulated list when pointer located on head of list
struct Node *getNextNode(struct Node *head);

//=============================================================================
//	Function which start msg
int init_msg(const int ext_key);

//=============================================================================
//	Function which close the msg system
void close_msg(const int queue_id);

//=============================================================================
//	Function which set signal handler
void setHandlers();

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************


//=============================================================================
//	Main function
int main(int argc, char **argv)
{
	int 			queue_id 	= 	0,
	 				ext_key		=	0;
	struct Node 	*head 		= 	NULL;		//	DB of list
	double 			pai_res		=	0;			//	pi variable

	// If the user enter nesesery data corect:
	if(argc != 3)
	{
		incorect_param();						//	print error
		exit(EXIT_FAILURE);
	}
	
	setHandlers();								//	set signal handlers
	
	ext_key 	= 	atoi(argv[1]);				//	get external key	
	alarm(atoi(argv[2]));						//	set alarm 

	queue_id 	= 	init_msg(ext_key);			//	init msg
	head 		= 	retreive_data(queue_id);	//	retreive msg
	close_msg(queue_id);						//	close msg
		
	//if(head!= NULL)
	//{
		pai_res = 	calcAverage(head);			//	get value of pi
		print_result(pai_res);					//	print reults
		clear_memory(head);						//	clear memory used
	//}

	return(EXIT_SUCCESS);

}

//=============================================================================
//	Function which set signal handler
void setHandlers()
{
	signal(SIGALRM, stopServer);		//	set signal handler for Alarm 
	signal(SIGINT, stopServer);			//	set signal handler for sigInt

}

//=============================================================================
//	Function which start msg
int init_msg(const int ext_key)
{
	int 			queue_id = 0;		//			msg desc id
	key_t 			key;				//			ftok key
	
	if((key = ftok("/tmp", ext_key)) == -1)
		errExit("ftok()failed\n");		//			Print error and exit
	if((queue_id = msgget(key,MSGGET_FLAG)) == -1)
		errExit("msgget()failed\n");	//			Print error and exit
	
	return(queue_id);					//			return msg desc id

}

//=============================================================================
//	Function which close the msg system
void close_msg(const int queue_id)
{
	if(msgctl(queue_id, IPC_RMID, NULL) == -1)
		errExit("msgctl()failed\n");	//			print error and exit

}

//=============================================================================
//	Function which retreive data and insert to list
//	Get the message queue_id
//	Return List
struct Node *retreive_data(const int queue_id)
{

	struct my_msgbuf 	my_msg;
	int 				status;
	long int 			allowed_type 	= 	0;	//TODO
	struct Node 		*head 			= 	NULL;
	
	while(!quit)
	{			
		status = msgrcv(queue_id,(struct msgbuf*)&my_msg, MAX_MSG_LEN, allowed_type, IPC_NOWAIT);
		if(status > 0)
		{
			head= getNextNode(head);		//	manipulation with list
			head->msgStorge = my_msg;		//	copy data recived			
		}
		
		sleep(1);							//	sleep
	}

	return(head);

}

//=============================================================================
//	Function which manipulate whith list
//	For insert every new node to head of list
//	Return manipulated list when pointer located on head of list
struct Node *getNextNode(struct Node *head)
{
	struct Node *temp 	= 	NULL;		//	temporary variable

	if(head == NULL)					//	if list empty yet
		head = Allocate_Node();			//	create new node
	else
	{									//	if list not empty
		temp = Allocate_Node();			//	crerate new node
		temp->_next = head;				//	new node point to head of list
		head = temp;					//	new node be head of list
	}
	
	return(head);						//	return head of list
		
}

//=============================================================================
//	function which print pi
void print_result(const double pai)
{
	fprintf(stdout,"pai = %.10f\n", pai);	//	print to stdout

}

//=============================================================================
//	function which allocate new cell 
//	return pointer to new cell
struct Node *Allocate_Node()
{
	struct Node *temp = NULL;			//	temp variable
	
	temp = malloc(sizeof(struct Node));	//	allocate new node
	
	if(temp == NULL)	//	if not success allocate new node
		errExit("Can not allocate memory.\n");
	
	temp->_next = NULL;	//	set pointer to next be NULL
	
	return(temp);		//	return new node

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
	struct Node *temp = NULL;		//	temp variable
	
	while(head != NULL)				//	while the node is not null
	{
		temp = head->_next;			//	set temp be next
		free(head);					//	delete this
		head= temp;					//	next be this
	}
	
}

//=============================================================================
//	Function ti calculate Pi over all clients was geted
// Inpu-t:	data geted by server in list
// Return:	value of PI
double calcAverage(struct Node *nod)
{
	double 		average 	= 	0;		//	TODO
	long int 	divides 	= 	0;		//	TODO
	struct Node *temp 		= 	NULL;	//	temp variable

	temp = nod;							//	get head of list

	while(temp!=NULL)
	{									//	TODO
		average += temp->msgStorge.mtype * atof(temp->msgStorge.mtext);
		divides += temp->msgStorge.mtype;
		temp = temp->_next;				//	get next node in list
	}

	if(divides)							//	check if can devide
	{
		average = average / divides;	//	deviding
		return (average);				//	return value
	}

	return (0);							//	return other value
	
}

//=============================================================================
//	print message of incorrect input parameters
void incorect_param()
{
	printf("You need enter 2 parameters:\n");
	printf("1. queue_id\n");
	printf("2. time for timer\n");

}

//=============================================================================
// A handler function
//	Updating gloabal to exit from program
void stopServer(int sig_num)
{
	quit = 1;							//	exit status from program

}

//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================

