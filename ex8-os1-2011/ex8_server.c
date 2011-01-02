/*

	Provide server for clients which calculated pi
	and send it to server.
	Server waiting X second and wait for argv[3] .X mast be provided in argv-2.
*/

//                               Include section
//=============================================================================
#include <stdio.h>
#include <unistd.h>				// for rea/write/close
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>			// for htonl(),....
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>				// for using signals

#define BUF_LEN 13
#define SIZE_BACKLOG_QUEUE 5	// size of the backlog queue




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
//	function which reteive data from clients
//	getting main socket file descriptor and number of port
double retreive_data(int main_socket, int port);

//=============================================================================
//	function which init the server to listen to clients.
//	getting: pointer to destination adrres stucture, main socket file
//	descriptorand and port number.
void start_to_listen(struct sockaddr_in *my_address, int main_socket,
					 int port);

//=============================================================================
//	function which preper main socket adrres structure
//	getting: pointer to destination adrres stucture and port number
struct sockaddr_in *prep_main_sock_addr_strac(struct sockaddr_in *my_address,int port);

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
void read_from_socket(int serving_socket,
					  double *pai_integrator,
					  int *pai_divides);

//=============================================================================
//	function which unpack pai result and multiplier to to double and int
// 	getting: meseg bufer, pai integrator and pai divides.
void unpack_msg_buf(char msg_buf[],
					double *pai_integrator,
					int *pai_divides);

	int		main_socket	= 0;   //socket file descriptor for receive applicatoin
//*****************************************************************************
//*****************************************************************************

//=============================================================================
//	Main function
int main(int argc, char **argv)
{


	int		time_period = 0;						// timer of working time
	double 	pai_res	= 0;							// pi variable

	if(argc != 3)			  // If the user enter nesesery data corect:
		incorect_param();									// print error

	time_period = chek_time(atoi(argv[1]));					// working time

	printf("Time is %d\n",time_period);

	main_socket = init_socket();							// init socket

	print_welcome_message(time_period);

	setHandlers();									// set signal handlers

	alarm(time_period);								//	set alarm

	pai_res = retreive_data(main_socket, atoi(argv[2]));// get data from clients

	if(pai_res)
		print_result(pai_res);							//	print reults

	close(main_socket);			// close serving_socket

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
double retreive_data(int main_socket, int port)
{
	double	pai_integrator	= 0;		// integrated pai result from clients
	int 	pai_divides		= 0;		// sum of multipls for calculation of
										// avarage

	struct sockaddr_in my_address;		// server address (for bing())
	struct sockaddr_in client_address;	// client address (for accept()
	socklen_t size_cliet_addr = sizeof(client_address);
	int	serving_socket;   	// socket file descriptor for serving applicatoin

	// start listen to clients
	start_to_listen(&my_address, main_socket, port);

	while(!quit)
	{
		// get new application and redirect it to seperated socket
	printf("PYO\n");
		if((serving_socket = accept(main_socket,(struct sockaddr*)&client_address, &size_cliet_addr))< 0)
			continue;
	printf("PYO2\n");
		//read from serving socked (recive data from client)
		read_from_socket(serving_socket, &pai_integrator, &pai_divides);

		close(serving_socket);			// close serving_socket

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
void start_to_listen(struct sockaddr_in *my_address, int main_socket, int port)
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
struct sockaddr_in *prep_main_sock_addr_strac(struct sockaddr_in *my_address,int port)
{
	// preper socket adrres structure
	(*my_address).sin_family 	= AF_INET;
	(*my_address).sin_port		= htons(port);
	(*my_address).sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr("10.2.10.25")
	memset((*my_address).sin_zero, '\0', sizeof((*my_address).sin_zero));

	return(my_address);
}

//=============================================================================
//	Function which read from socket (resive data from client)
//	getting: socket file descriptor and buffer of  messeg (pai value)
void read_from_socket(int serving_socket,
					  double *pai_integrator,
					  int *pai_divides)
{
	char msg_buf[BUF_LEN];							// meseg buffer

	if((read(serving_socket, msg_buf, BUF_LEN)) == -1)
		errExit("read() from client failed\n");		//	Print error and exit


	unpack_msg_buf(msg_buf, pai_integrator, pai_divides);

}

//=============================================================================
//	function which unpack pai result and multiplier to to double and int
// 	getting: meseg bufer, pai integrator and pai divides.
void unpack_msg_buf(char msg_buf[],
					double *pai_integrator,
					int *pai_divides)
{

	// convert last char at string to int that  temprorary save divides value
	int temp_divides = msg_buf[BUF_LEN -1] - '0';

	msg_buf[BUF_LEN-1] = '\0';	// remove last char from pai value
	
	//printf("divider %d\n",temp_divides);

	//printf("int: %f \n",atof(msg_buf));
	(*pai_integrator) += atof(msg_buf) * temp_divides;	// update pai integrtor

	(*pai_divides) += temp_divides;						// update pai divides

}

//=============================================================================
//	function cheking if the user gave a ligal time for timer.
//	retur: timer value if avry thing ok, othewise exiteng program.
int chek_time(int input)
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
	printf("SIG\n");
	close(main_socket);
	quit = 1;							//	exit status from program

}

//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================

