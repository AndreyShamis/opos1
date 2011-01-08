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
void print_menu()
{
	fprintf(stdout,"\n \
	\t# 1 - Write 1 for check ID \n \
	\t# 2 - Write 2 for get pi by Monte Carlo\n");

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
void checl_client_creation(CLIENT *cl,char *server)
{
	if(cl == NULL)
	{
		clnt_pcreateerror(server);
		exit(EXIT_FAILURE);
	}

}

//=============================================================================
void Check_Id(CLIENT *cl,char *server)
{

	int *result;
	char *message;
	char id_str[MAX_ID_LEN];
		
	fprintf(stdout,"\nPlease write ID which you want to check:\t");	
	fgets(id_str,MAX_ID_LEN,stdin);

	message = id_str;
	result = is_valid_id_1(&message,cl);	
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
int check_multiplier(const int multi_p)
{
	if(multi_p<MIN_MULTIPLIER || multi_p > MAX_MULTIPLIER)
	{
		fprintf(stderr,"Bad multiplier!\n");
		return(0);
	}
	
	return(1);
	
}

//=============================================================================
void getPi(CLIENT *cl,char *server)
{
	int multiplier=0;
	double 	*val;
	char hren;
	
	fprintf(stdout,"\nPlease write digit [1-6]:\t");
	fscanf(stdin,"%d%c",&multiplier,&hren);

	if(check_multiplier(multiplier))
	{
		val = estimate_pi_1(&multiplier,cl);	
	
		if(val == NULL)
		{	
			clnt_perror(cl,server);
			exit(EXIT_FAILURE);
		}
		printf("The pi is %1.10lf\n",*val);
	}

}

//=============================================================================
int main(int argc,char **argv)
{
	CLIENT 		*cl;
	char 		*server;
	int 		counter = 0;
	short int 	input	= 0;
	char 		hren;

	check_correct_start(argc);
	server 	= 	argv[1];
		
	cl = clnt_create(server,REMOTE_PROG_SKELETON,MESSAGEVERS,"tcp");
		
	for(counter=0;counter< MAX_CYCLES;counter++)
	{
		print_menu();
		fscanf(stdin,"%hd%c",&input,&hren);
		
		if(input == CHECK_ID)
			Check_Id(cl,server);
		else if(input == GET_PI)
			getPi(cl,server);
		else
			fprintf(stdout,"You mast select or 1 or 2 only\n");
				
	}

	clnt_destroy(cl);
	
	return(EXIT_SUCCESS);	
}
