/*

	Provide server for clients which calculated pi
	Server waiting X=argv[1] seconds and waiting for connections on port
	Y=argv[2]
	Handling connection happens immediately, and then counted for 
	the math task. After a timeout the server receives the signal and 
	then used it closes out the connection.
*/

//                               Include section
//=============================================================================
#include <stdio.h>
#include <unistd.h>				// for read/write/close/alarm
#include <string.h>				//	using in memset
#include <stdlib.h>
#include <sys/socket.h>			// for htonl(),....
#include <netinet/in.h>			//	for net
#include <signal.h>				// for using signals

#define BUF_LEN 13
#define SIZE_BACKLOG_QUEUE 5	// size of the backlog queue




//                       	  globals section
//=============================================================================
int	serving_socket;   	// 	socket file descriptor for serving applicatoin
int	main_socket;   	//	socket file descriptor for receive applicatoin
int quit = 0;		//	global exit variable

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
//	function which reteive data from clients
//	getting main socket file descriptor and number of port
double retreive_data(const int port);

//=============================================================================
//	function which init the server to listen to clients.
//	getting: pointer to destination adrres stucture, main socket file
//	descriptorand and port number.
void start_to_listen(struct sockaddr_in *my_address,const int port);

//=============================================================================
//	function which preper main socket adrres structure
//	getting: pointer to destination adrres stucture and port number
struct sockaddr_in *prep_main_sock_addr_strac(struct sockaddr_in *my_address,
									const int port);

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
//	function cheking if the user gave a ligal time for timer.
//	retur: timer value if avry thing ok, othewise exiteng program.
int chek_time(int input);

//=============================================================================
//	Function which read from socket (resive data from client)
//	getting: socket file descriptor and buffer of  messeg (pai value)
void read_from_socket(double *pai_integrator,int *pai_divides);

//=============================================================================
//	function which unpack pai result and multiplier to to double and int
// 	getting: meseg bufer, pai integrator and pai divides.
void unpack_msg_buf(char msg_buf[],	double *pai_integrator,
					int *pai_divides);
//*****************************************************************************
//*****************************************************************************

//=============================================================================
//	Main function
int main(int argc, char **argv)
{

	int		time_period = 0;						// timer of working time
	double 	pai_res	= 0;							// pi variable

	if(argc != 3)			  // If the user enter nesesery data corect:
		incorect_param();							// print error

	time_period = chek_time(atoi(argv[1]));			// working time
	print_welcome_message(time_period);
	setHandlers();									// set signal handlers
	alarm(time_period);								//	set alarm
	
	main_socket 	= init_socket();				// init socket
	pai_res 		= retreive_data(atoi(argv[2]));	// get data from clients

	if(pai_res)
		print_result(pai_res);						//	print reults

	close(main_socket);								// close serving_socket

	return(EXIT_SUCCESS);

}


//                             Function section
//=============================================================================

//=============================================================================
//	Function which init socket
//	return socket file descriptor
int init_socket()
{
	int my_socket;

	if((my_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)//allocate socket
		errExit("socket: allocation failed\n");		//	Print error and exit

	return my_socket;
}

//=============================================================================
//	function which reteive data from clients
//	getting main socket file descriptor and number of port
double retreive_data(const int port)
{
	double	pai_integrator	= 0;		// integrated pai result from clients
	int 	pai_divides		= 0;		// sum of multipls for calculation of
										// avarage

	struct sockaddr_in my_address;		// server address (for bing())
	struct sockaddr_in client_address;	// client address (for accept()
	socklen_t size_cliet_addr = sizeof(client_address);

	// start listen to clients
	start_to_listen(&my_address, port);

	while(!quit)
	{
		// get new application and redirect it to seperated socket
		if((serving_socket = accept(main_socket,
		  (struct sockaddr*)&client_address, &size_cliet_addr))< 0)
			continue;

		//read from serving socked (recive data from client)
		read_from_socket(&pai_integrator, &pai_divides);

	}

	if(pai_divides)						//	check if can devide
		return (pai_integrator / pai_divides);
	else
		return (0);

}

//=============================================================================
//	function which init the server to listen to clients.
//	getting: pointer to destination adrres stucture, main socket file
//	descriptorand and port number.
void start_to_listen(struct sockaddr_in *my_address, const int port)
{
	// prepare main socket addres structur
	my_address = prep_main_sock_addr_strac(my_address,port);

	// conect between main socket and address
	if((bind(main_socket, (struct sockaddr*)my_address,
		sizeof(*my_address))) == -1)
		errExit("bind()failed\n");			//	Print error and exit

	if((listen(main_socket,SIZE_BACKLOG_QUEUE)) == -1)
		errExit("listen()failed\n");		//	Print error and exit

}

//=============================================================================
//	function which preper main socket adrres structure
//	getting: pointer to destination adrres stucture and port number
struct sockaddr_in *prep_main_sock_addr_strac(struct sockaddr_in *my_address,
										const int port)
{
	// preper socket adrres structure
	(*my_address).sin_family 	= AF_INET;
	(*my_address).sin_port		= htons(port);
	(*my_address).sin_addr.s_addr = htonl(INADDR_ANY);
	memset((*my_address).sin_zero, '\0', sizeof((*my_address).sin_zero));

	return(my_address);
	
}

//=============================================================================
//	Function which read from socket (resive data from client)
//	getting: buffer of  messeg (pai value)
void read_from_socket(double *pai_integrator,int *pai_divides)
{
	char msg_buf[BUF_LEN];							// meseg buffer

	if(!quit &&(read(serving_socket, msg_buf, BUF_LEN)) == -1)
		errExit("read() from client failed\n");		//	Print error and exit

	close(serving_socket);			// close serving_socket
	
	unpack_msg_buf(msg_buf, pai_integrator, pai_divides);

}

//=============================================================================
//	function which unpack pai result and multiplier to to double and int
// 	getting: meseg bufer, pai integrator and pai divides.
void unpack_msg_buf(char msg_buf[],double *pai_integrator,int *pai_divides)
{

	// convert last char at string to int that  temprorary save divides value
	int temp_divides = msg_buf[BUF_LEN -1] - '0';

	msg_buf[BUF_LEN-1] = '\0';	// remove last char from pai value

	(*pai_integrator) += atof(msg_buf) * temp_divides;	// update pai integrtor

	(*pai_divides) += temp_divides;						// update pai divides

}

//=============================================================================
//	function cheking if the user gave a ligal time for timer.
//	retur: timer value if avry thing ok, othewise exiteng program.
int chek_time(const int input)
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
//	Printing Starting welcome message
void print_welcome_message(const int time)
{
	printf("\n\n\t-Server started!\n");
	fprintf(stdout,"\t-\t#\tTime for timer\t:%d\n",time);
	printf("\t + Waitng for clients.......\n");

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
	quit = 1;
	close(main_socket);				//	close opened sockets
	close(serving_socket);			//	close opened sockets

}

//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================

