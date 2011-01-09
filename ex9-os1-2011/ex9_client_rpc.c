#include <stdio.h>
#include "/usr/include/rpc/rpc.h"
#include "ex9_server.h"

#define MAX_CYCLES 4				//	number of cicles
#define MAX_ID_LEN 10				//	size of string for id

#define NUMBER_OF_PARAM 2			//	number of parameter needed
#define CHECK_ID 1					//	define for check ID
#define GET_PI 2					//	define for get Pi
#define MIN_MULTIPLIER 1			//	Minimal Pi divider
#define MAX_MULTIPLIER 6			//	Maximal Pi Divider

//=============================================================================
//	Function which printing user menu
void print_menu();

//=============================================================================
//	Function which check if numer of parameters which get program is correct
//	Return 1 if correct 
//	else print error end exit from pragram
int check_correct_start(const int argc);

//=============================================================================
//	Function which check if client creation success
//	if not report about error and exit from programm
void checl_client_creation(CLIENT *cl,char *server);

//=============================================================================
//	Function which get client and server then geting from the user
//	the string which gona be checking by server to ID
//	Printing the result to screen
void Check_Id(CLIENT *cl,char *server);

//=============================================================================
//	Function which check if multiplier is good thats mean not biger or small
//	Return 1 if good and 0 if not good
int check_multiplier(const int multi_p);

//=============================================================================
//	Function which getint the client and server char then getting multiplier
//	from user and sending it to server. After retreiving data(result) from
//	server put-out is to the screen
void getPi(CLIENT *cl,char *server);

//=============================================================================
int main(int argc,char **argv)
{
	CLIENT 		*cl;				//	client variable
	char 		*server;			//	server using variable
	int 		counter = 0;		//	for variable
	short int 	input	= 0;		//	menu variable
	char 		hren;				//	help variable

	check_correct_start(argc);		//	check if number of param correct
	server 	= 	argv[1];			//	get the server host
		
	//	creating connection
	cl = clnt_create(server,REMOTE_PROG_SKELETON,MESSAGEVERS,"tcp");
	
	//	while counter < cycles need 
	for(counter=0;counter< MAX_CYCLES;counter++)
	{
		print_menu();						//	print indication menu
		fscanf(stdin,"%hd%c",&input,&hren);	//	get menu option
		
		if(input == CHECK_ID)					
			Check_Id(cl,server);			//	check id
		else if(input == GET_PI)
			getPi(cl,server);				//	get pi
		else								//	print correction to user
			fprintf(stdout,"You mast select or 1 or 2 only\n");
				
	}

	clnt_destroy(cl);				//	destroy connection
	
	return(EXIT_SUCCESS);			//	exit from program
}

//=============================================================================
//	Function which getint the client and server char then getting multiplier
//	from user and sending it to server. After retreiving data(result) from
//	server put-out is to the screen
void getPi(CLIENT *cl,char *server)
{
	int 	multiplier=0;	//	value be sended to server multiplier
	double 	*val;			//	value retuned from server
	char 	hren;			//	help varibale used in fscanf
	
	//	indicaton to user what need to do
	fprintf(stdout,"\nPlease write digit [1-6]:\t");
	//	get multiplier from user
	fscanf(stdin,"%d%c",&multiplier,&hren);
	//	check if the multiplier value is good
	if(check_multiplier(multiplier))
	{
		//	send it to server and retrive result
		val = estimate_pi_1(&multiplier,cl);	
		//	check if result not null
		if(val == NULL)
		{	
			clnt_perror(cl,server);
			exit(EXIT_FAILURE);
		}
		//	print result
		printf("The pi is %1.10lf\n",*val);
	}

}

//=============================================================================
//	Function which check if multiplier is good thats mean not biger or small
//	Return 1 if good and 0 if not good
int check_multiplier(const int multi_p)
{
	//	checking
	if(multi_p<MIN_MULTIPLIER || multi_p > MAX_MULTIPLIER)
	{
		//	Print error return 0
		fprintf(stderr,"Bad multiplier!\n");
		return(0);
	}
	
	return(1);			//	if good return 1
	
}

//=============================================================================
//	Function which get client and server then geting from the user
//	the string which gona be checking by server to ID
//	Printing the result to screen
void Check_Id(CLIENT *cl,char *server)
{

	int *result;					//	pointer to result	
	char *message;					//	pointer to message
	char id_str[MAX_ID_LEN];		//	string for ID input
		
	//	Indication to user what need to do
	fprintf(stdout,"\nPlease write ID which you want to check:\t");	
	fgets(id_str,MAX_ID_LEN,stdin);	//	get from the user ID

	message = id_str;				//	set pointer
	result = is_valid_id_1(&message,cl);	//	send question get result
	
	if(result == NULL)
	{	
		clnt_perror(cl,server);
		exit(EXIT_FAILURE);
	}

	if(*result != 0)
		printf("(%d)The id is correct\n",*result);
	else
		printf("(%d)The id is INCORRECT\n",*result);

}

//=============================================================================
//	Function which check if numer of parameters which get program is correct
//	Return 1 if correct 
//	else print error end exit from pragram
int check_correct_start(const int argc)
{
	//	check if number of parameter eqivalent to number needed
	if(argc == NUMBER_OF_PARAM)
		return(1);

	//	number of paramter bad, print error message and exit
	fprintf(stderr,"Incorrect number of parameters\n");
	exit(EXIT_FAILURE);
	
	return(0);

}

//=============================================================================
//	Function which check if client creation success
//	if not report about error and exit from programm
void checl_client_creation(CLIENT *cl,char *server)
{
	//	check if client is null
	if(cl == NULL)
	{	
		//	then report error and exit from the program
		clnt_pcreateerror(server);
		exit(EXIT_FAILURE);
	}

}

//=============================================================================
//	Function which printing user menu
void print_menu()
{
	fprintf(stdout,"\n \
	\t# 1 - Write 1 for check ID \n \
	\t# 2 - Write 2 for get pi by Monte Carlo\n");

}
//=============================================================================
//=============================================================================
//=============================================================================
