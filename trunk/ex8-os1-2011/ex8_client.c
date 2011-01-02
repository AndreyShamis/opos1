/*
	This file are client which connected to server and send him
	the pi value are is calculeted in function culcPai by MonteCarlo method.
	The connect with using tcp/ip
	The client can get two tipes of adress
	First is simple ip address	
	Second is domain name.
	First Parameter which client get is ip adress or host name of serever
	Second is port
	Third is multiplier used in monte carlo method which can be between 1-5
	
*/
//                               Include section
//=============================================================================
#include <stdio.h>
#include <unistd.h>			// for rea/write/close
#include <string.h>			//	need for do memset
#include <stdlib.h>
#include <time.h>			//	used in rand and geted time
#include <sys/socket.h>		// for htonl(),....
#include <arpa/inet.h>		//	for inet_pton
#include <netdb.h>			//	for gethostbyname

#define HOST_ADDR_LEN 20
#define BUF_LEN 13

#define MIN_MULTIPLIER 1		//	Multiplier minimal value
#define MAX_MULTIPLIER 5		//	Multiplier maximal value

//                             Prototypes section
//=============================================================================

//=============================================================================
//	print message of incorrect input parameters
void incorect_param();
//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(const char *msg);

//=============================================================================
//	Function which init socket
//	return socket file descriptor
int init_socket();

//=============================================================================
//	function which connect socket to the server
//	getting socket file descriptor, pointer to host addres string and
//	destination port number
void connect_to_server(const int my_socket, char **host_addr, 
									const int dest_port);

//=============================================================================
//	function which preper socket adrres structure
//	getting: pointer to destination adrres stucture, pointer to host addres
//	string and destination	port number
void prep_sock_addr_strac(struct sockaddr_in *dest_addr, char **host_addr,
						  const int dest_port);
//=============================================================================
//	function wich get input for multiplayer end check if its corretc
//	if yes return the real value else print error and exit
int checkMultiPlaier(const int input);

//=============================================================================
//	function to calculate Pi
//	geting multiplayer
//	return claculated value
double culcPai(const int multiplier);

//=============================================================================
//	function which pack pai result and multiplier to single string
// 	getting: meseg bufer, pai result and multiplier.
void prep_msg_buf(char buf[], double pai_calculated, int multiplier);

//=============================================================================
//	Function which write to socket (send data to server)
//	getting: socket file descriptor and buffer of  messeg (pai value)
void write_to_socket(const int my_socket,const char buf[]);

//=============================================================================
//	function wich get some string and trying to checl if this 
//	is correct ipAddress
//	return 0 if not else some int if yes
int isValidIpAddress(const char *ipAddress);

///////////////////////////////////////////////////////////////////////////////
//                                Main section
//=============================================================================
int main(int argc, char **argv)
{
	int		my_socket;								// socket file descriptor
	int 	multiplier ;							// multiply rand size
	char	buf[BUF_LEN];							// meseg buffer
	double	pai_calculated;							// pai result

	if(argc != 4)		// If the user enter nesesery data corect:
		incorect_param();							//	print error
	multiplier 	= checkMultiPlaier(atoi(argv[3]));	//	get multiplier
	my_socket 	= init_socket();					// init socket

	// connect socket to server
	connect_to_server(my_socket, &argv[1], atoi(argv[2]));

	pai_calculated 	=	culcPai(multiplier);		// calc pai.

	// pack pai result and multiplier to single string
	prep_msg_buf(buf, pai_calculated, multiplier);

	write_to_socket(my_socket, buf);				// write to socket

	close(my_socket);

	return(EXIT_SUCCESS);

}


//                             Function section
//=============================================================================
//	function wich get input for multiplayer end check if its corretc
//	if yes return the real value else print error and exit
int checkMultiPlaier(const int input)
{
	if(input >= MIN_MULTIPLIER && input <=MAX_MULTIPLIER)
		return(input);
	else
	{
		fprintf(stderr,"Incorect paramter for miltiplaier\n");
		exit(EXIT_FAILURE);
	
	}
}

//=============================================================================
//	function wich get some string and trying to checl if this 
//	is correct ipAddress
//	return 0 if not else some int if yes
int isValidIpAddress(const char *ipAddress)
{

    struct sockaddr_in sa;		//	struct for inetpton use
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
		
    return result != 0;			//	return value

}

//=============================================================================
//	Function which init socket
//	return socket file descriptor
int init_socket()
{
	int my_socket;					//	my socket int

	if((my_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)//allocate socket
		errExit("socket: allocation failed\n");		//	Print error and exit

	return my_socket;				//	return value
}

//=============================================================================
//	function which connect socket to the server
//	getting: pointer to socket, pointer to host addres string and destination
//	port number
void connect_to_server(const int my_socket, char **host_addr, 
									const int dest_port)
{
	struct sockaddr_in dest_addr;	// for creation of conection with server

	// prepare socket addres structur
	prep_sock_addr_strac(&dest_addr, host_addr, dest_port);

	// connect socket to the server
	if((connect(my_socket,(struct sockaddr*)&dest_addr,
		sizeof(dest_addr))) == -1)
		errExit("connect()failed\n");		//	Print error and exit


}

//=============================================================================
//	function which preper socket adrres structure
//	getting: pointer to destination adrres stucture, pointer to host addres
//	string and destination	port number
void prep_sock_addr_strac(struct sockaddr_in *dest_addr, char **host_addr,
						 const int dest_port)
{

	// preper socket adrres structure
	(*dest_addr).sin_family 		= AF_INET;
	(*dest_addr).sin_port			= htons(dest_port);
	
	//	ip or hostname manipulation
	if(isValidIpAddress(*host_addr))	//	in case with ip
		(*dest_addr).sin_addr.s_addr 	= inet_addr(*host_addr);
	else
	{									//	in case with host name
		struct hostent *he;				//	hostname struct
		if((he = gethostbyname(*host_addr)) != NULL)	//	get hostbyname
			(*dest_addr).sin_addr	= *((struct in_addr *)he->h_addr);
		else
			errExit("Can not get host by name\n");
	}
	memset((*dest_addr).sin_zero, '\0', sizeof((*dest_addr).sin_zero));

}

//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(const char *msg)
{
	perror(msg);						//	Print message
	exit(EXIT_FAILURE);					//	exit whith failure

}

//=============================================================================
//	print message of incorrect input parameters
void incorect_param()
{
	fprintf(stderr,"You need enter 2 parameters:\n \
		\r1. ip addres or hostname \n \
		\r2. port number of server  \n \
		\r3. Multiplier for rand\n");
	exit(EXIT_FAILURE);

}

//=============================================================================
//	function to calculate Pi .geting multiplayer
//	return claculated value
double culcPai(const int multiplier)
{
	double xVal,							// rndom x coordinate value.
		   yVal,							// rndom y coordinate value.
		   distance,						// distance of points.
		   totalPoints 	= multiplier * 10000,// difine total points number.
		   pointsIn 	= 0;
	int index;	// for Looping.

	srand(time(NULL));	// init random.

	// Loop thrugh all random points, and calculate num of point in the circel.
	for(index = 0; index < totalPoints; index ++)
	{
		xVal = (double) rand()/RAND_MAX;
		yVal = (double) rand()/RAND_MAX;

		// alculate num of point in the circel
		distance = (xVal * xVal) + (yVal * yVal);
		distance = distance * distance;

		if(distance <= 1)
			pointsIn ++;
	}

	// return pai propabilety value.
	return (4 * (pointsIn / totalPoints));

}

//=============================================================================
//	function which pack pai result and multiplier to single string
// 	getting: meseg bufer, pai result and multiplier.
void prep_msg_buf(char buf[], double	pai_calculated, int multiplier)
{
	// convert pai (doubel type) to string type
	sprintf(buf, "%.10f\n",pai_calculated);

	buf[BUF_LEN -1] = (multiplier + '0');	// put at last sell multiplier value

}

//=============================================================================
//	Function which write to socket (send data to server)
//	getting: socket file descriptor and buffer of  messeg (pai value)
void write_to_socket(const int my_socket,const char buf[])
{
	if((write(my_socket, buf, BUF_LEN)) == -1)
		errExit("write() to server failed\n");		//	Print error and exit

}

//=============================================================================
//=============================================================================
//=============================================================================
