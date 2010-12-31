/*

	Provide server for clients which calculated pi
	and send it to server.
	Server waiting X second and wait for argv[3] .X mast be provided in argv-2.
*/

//                               Include section
//=============================================================================
#include <stdio.h>
#include <unistd.h>			// for rea/write/close
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>		// for htonl(),....
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>			// for using signals

#define HOST_ADDR_LEN 20
#define BUF_LEN 13



//                       	  globals section
//=============================================================================
int quit = 0;	//global variable to get exit status can be updated in handler


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
//	Function which init socket
//	return socket file descriptor
int init_socket();

//=============================================================================
//	Function ti calculate Pi over all clients was geted
// Inpu-t:	pointer to the shered memory, data base size
// Return:	value of Pai
double calcAverage(struct my_msgbuf *data_base,const int counter,
												const int shm_size);

//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(const char *msg);

//=============================================================================
//	function which print pi
void print_result(const double pai);


//=============================================================================
//	Function which set signal handler
void setHandlers();

//=============================================================================
//	Printing Starting welcome message
void print_welcome_message(const int time);


//=============================================================================
//	Function which make dilay for witen to data at shered memory.
void wait_for_data(int *counter,const int timer,
				const int shm_id,const int shm_size);

//=============================================================================
//	get corrected time which prgram be worked
int get_time_correct_period(int input);


//*****************************************************************************
//*****************************************************************************

//=============================================================================
//	Main function
int main(int argc, char **argv)
{

	int		my_socket;								// socket file descriptor
	int 	multiplier = atoi(argv[3]);				// multiply rand size
	char	buf[BUF_LEN];							// meseg buffer
	double 	pai_res	= 0;							// pi variable

	if(argc != 3)				// If the user enter nesesery data corect:
		incorect_param();							// print error

	time_period = get_time_correct_period(atoi(argv[2]));	// working time

	my_socket = init_socket();						// init socket

	print_welcome_message(time_period);

	setHandlers();									// set signal handlers

	// waiting for shered memory to be filled.
	wait_for_data(counter,time_period, shm_id, shm_size);

	pai_res = calcAverage(data_base, (*counter), shm_size);	//	get value of pi

	if(pai_res)
		print_result(pai_res);				//	print reults


	return(EXIT_SUCCESS);

}

//=============================================================================
//	get corrected time which prgram be worked
int get_time_correct_period(int input)
{
	if(input > 0)
		return(input);
	else
	{
		//Print error and exit
		fprintf(stderr,"Incorrect time, it is must be >0\n");
		exit(EXIT_FAILURE);
	}
	return(0);

}

//=============================================================================
//	Function which init socket
//	return socket file descriptor
int init_socket()
{
	int my_socket;

	if((my_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1)//allocate socket
		errExit("socket: allocation failed\n");		//	Print error and exit

	return my_socket;
}



//=============================================================================
//	Printing Starting welcome message
void print_welcome_message(const int time)
{
	printf("\n\n\t-Server started!\n");
	fprintf(stdout,"\t-\t#\tTime for timer\t:%d\n",time);
	printf("\t + Waitng for clients.......\n");

}



//=============================================================================
//	Function which make dilay for witen to data at shered memory.
void wait_for_data(int *counter,const int timer,
				const int shm_id,const int shm_size)
{
	alarm(timer);						//	set alarm

	while(!quit)			 // beasy wait for clients that fill the SHM
		if((*counter) ==  0) // lock SHM if the clients used all SHM
			lock_shm(shm_id);

}

//=============================================================================
//	Function which set signal handler
void setHandlers()
{
	signal(SIGALRM, stopServer);		//	set signal handler for Alarm
	signal(SIGINT, stopServer);			//	set signal handler for sigInt

}

//=============================================================================
//	function which print pi
void print_result(const double pai)
{
	fprintf(stdout,"PI(pay) is\t = %.10f\n", pai);	//	print to stdout

}

//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(const char *msg)
{
	perror(msg);					//	print err message
	exit(EXIT_FAILURE);				//	exit whith fail

}

//=============================================================================
//	Function ti calculate Pi over all clients was geted
// Inpu-t:	pointer to the shered memory, data base size
// Return:	value of Pai
double calcAverage(struct my_msgbuf *data_base,const int counter,
										const int shm_size)
{
	double 		average 	= 	0;		//	difine average of retreive pais.
	long int 	divides 	= 	0;		//	difine weight of calculation averag
	int 		index		=	0;		// for looping.
	fprintf(stdout,"Number of clients sended pi:%d\n", shm_size - counter);

	for(index = counter; index < shm_size; index++)
	{
		average += data_base[index].mtype * data_base[index].mtext;
		divides += data_base[index].mtype;
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
	fprintf(stderr,"You need enter 3 parameters:\n \
			\r1. time for timer\n			\
			\r2. port number\n");

	exit(EXIT_FAILURE);


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

