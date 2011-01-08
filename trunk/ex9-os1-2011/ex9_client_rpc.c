#include <stdio.h>
#include "/usr/include/rpc/rpc.h"
#include "ex9_server.h"

#define MAX_CYCLES 4
#define MAX_ID_LEN 9


void print_menu()
{
	fprintf(stdout,"Hello!\n \
	\tWrite 1 for check ID \n \
	\tWrite 2 for get pi by Monte Carlo\n");

}

int main(int argc,char **argv)
{
	CLIENT *cl;
	
	int *result;
	char *server;
	char *message;
	double val = 0;
	//double *dresult;
	
	//dresult = val;
	
	val = 3;
	server = argv[1];
	
	message = argv[2];
	if(argc !=3)
	{
		fprintf(stderr,"sdsd\n");
		exit(EXIT_FAILURE);
	}
	
	int counter = 0;
	int input = 0;
	for(counter=0;counter< MAX_CYCLES;counter++)
	{
		print_menu();
		fscanf(stdin,"%d",&input);
		
		if(input == 1)
		{
			char id_str[MAX_ID_LEN];
			fprintf(stdout,"Please write ID which you want to check\n");
			fgets(id_str,MAX_ID_LEN,stdin);

			cl = clnt_create(server,REMOTE_PROG_SKELETON,
							MESSAGEVERS,"tcp");
			if(cl == NULL)
			{
				clnt_pcreateerror(server);
				exit(EXIT_FAILURE);
		
	
			}
	
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
		else if(input == 2)
		{
		
		}
		
	}


	
	
	return(EXIT_SUCCESS);	
}
