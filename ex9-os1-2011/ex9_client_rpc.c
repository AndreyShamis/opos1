#include <stdio.h>
#include "/usr/include/rpc/rpc.h"
#include "ex9_server.h"

#define MAX_CYCLES 4
#define MAX_ID_LEN 10

#define NUMBER_OF_PARAM 2
#define CHECK_ID 1
#define GET_PI 2
#define MIN_MULTIPLIER 1
#define MAX_MULTIPLIER 6

//=============================================================================
void print_menu()
{
	fprintf(stdout,"\n \
	\t# 1 - Write 1 for check ID \n \
	\t# 2 - Write 2 for get pi by Monte Carlo\n");

}

//=============================================================================
int check_correct_start(const int argc)
{
	if(argc == NUMBER_OF_PARAM)
		return(1);

	fprintf(stderr,"Incorrect number of parameters\n");
	exit(EXIT_FAILURE);
	

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
		printf("The id is correct\n");
	else
		printf("The id is INCORRECT\n");

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
