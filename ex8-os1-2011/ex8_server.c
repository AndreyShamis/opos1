/*

	Provide server for clients which calculated pi
	and send it to server.
	Server waiting X second and wait for argv[3] .X mast be provided in argv-2.
*/

//                               Include section
//=============================================================================
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>		// for using SHM
#include <signal.h>			// for using signals


#define MSGGET_FLAG		IPC_CREAT | IPC_EXCL | 0600

//=============================================================================
//                        Variable and struct section

int quit = 0;	//global variable to get exit status can be updated in handler

//============================ STRUCTS ========================================
//	struct for retreidev messages
struct my_msgbuf
{
	short int mtype;				//	type of msgbuf
	double mtext;					//	double value
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
//	Function which create shered memory
int init_shm(const int ext_key,const int shm_size);

//=============================================================================
//	Function which set signal handler
void setHandlers();

//=============================================================================
//	Printing Starting welcome message
void print_welcome_message(const int time,const int mem_size);

//=============================================================================
//	Function which colse shered memory
void close_shm(const int shm_id);

//=============================================================================
//	Function which make dilay for witen to data at shered memory.
void wait_for_data(int *counter,const int timer,
				const int shm_id,const int shm_size);

//=============================================================================
//	Function which get pointer to shered memory
int *get_ptr_to_shm(const int shm_id);

//=============================================================================
//	get corrected time which prgram be worked
int get_time_correct_period(int input);

//=============================================================================
//	Function which lock access to shered memory  ot the claents.
void lock_shm(const int shm_id);
//=============================================================================
//	Get correct memory sizeof
int getMemoryCorrectSize(const int value);

//*****************************************************************************
//*****************************************************************************

//=============================================================================
//	Main function
int main(int argc, char **argv)
{
	int 			shm_id	= 	0,			//	internal comunication key
	 				ext_key		=	0,		//	external comunication key
	 				shm_size	=	0;		//	size of memory
	double 			pai_res		=	0;		//	pi variable
	int *counter 	= 	NULL;				//	pointer to counter
	int time_period	=	0;

	struct my_msgbuf *data_base = NULL;	// pointr to data base in shered memory
	setHandlers();						//	set signal handlers

	// If the user enter nesesery data corect:
	if(argc != 4)
		incorect_param();				//	print error

	time_period = 	get_time_correct_period(atoi(argv[2]));	// working time
	shm_size 	= 	getMemoryCorrectSize(atoi(argv[3]));// shered memory size
	ext_key 	= 	atoi(argv[1]);		//	get external key
	
	print_welcome_message(time_period,shm_size);
	
	shm_id 		= 	init_shm(ext_key, shm_size);//	init msg
	
	counter 	= 	get_ptr_to_shm(shm_id);		// pointer to the shered memo
	(*counter) 	= 	shm_size;					// set counter

	// get pointer to the arr of structs at shered memory
	data_base 	= (struct my_msgbuf*)(counter + 1);

	// waiting for shered memory to be filled.
	wait_for_data(counter,time_period, shm_id, shm_size);

	pai_res = calcAverage(data_base, (*counter), shm_size);	//	get value of pi

	if(pai_res)
		print_result(pai_res);				//	print reults

	close_shm(shm_id);						//	close shered memory

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
//	Function which lock access to shered memory  ot the claents.
void lock_shm(const int shm_id)
{
	struct shmid_ds shm_desc;						// struct for locking SHM

	if(shmctl(shm_id, SHM_LOCK, &shm_desc) == -1)	// lock SHM
		errExit("shmctl()failed\n");				//Print error and exit

}

//=============================================================================
//	Printing Starting welcome message
void print_welcome_message(const int time,const int mem_size)
{
	printf("\n\n\t-Server started!\n");
	fprintf(stdout,"\t-\t#\tTime for timer\t:%d\n",time);
	fprintf(stdout,"\t-\t#\tMemory size   \t:%d\n",mem_size);
	printf("\t + Waitng for clients.......\n");

}

//=============================================================================
//	Function which get pointer to shered memory
int *get_ptr_to_shm(const int shm_id)
{
	int *temp;							// temp pointer to SHM (type int)

	temp = (int*)shmat(shm_id, NULL, 0);// Get pointer to SHM
		if(!temp)
			errExit("shmatt()failed\n");//Print error and exit

	return (temp);

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
//	Function which colse shered memory
void close_shm(const int shm_id)
{
	struct shmid_ds shm_desc;	// struct for clousing SHM

	if(shmctl(shm_id, IPC_RMID, &shm_desc) == -1)	// close SHM
		errExit("shmctl()failed\n");	//			Print error and exit

}

//=============================================================================
//	Function which set signal handler
void setHandlers()
{
	signal(SIGALRM, stopServer);		//	set signal handler for Alarm
	signal(SIGINT, stopServer);			//	set signal handler for sigInt

}

//=============================================================================
//	Function which create shered memory
int init_shm(const int ext_key,const int shm_size)
{
	int 			shm_id = 0;			//			shm desc id
	key_t 			key;				//			ftok key

	if((key = ftok("/tmp", ext_key)) == -1)
		errExit("ftok()failed\n");		//			Print error and exit
	if((shm_id = shmget(key, sizeof(int) +
	   (sizeof(struct my_msgbuf) * shm_size), MSGGET_FLAG)) == -1)
		errExit("shmget()failed\n");	//			Print error and exit

	return(shm_id);						//			return shm desc id

}

//=============================================================================
//	function which print pi
void print_result(const double pai)
{
	fprintf(stdout,"PI(pay) is\t = %.10f\n", pai);	//	print to stdout

}

//=============================================================================
//	Get correct memory sizeof
int getMemoryCorrectSize(const int value)
{
	if(value >0)									//	check if value good
		return(value);								//	return value
	else
	{
		fprintf(stderr,"Incorrect memory size value\n");//	print error
		exit(EXIT_FAILURE);
	}	
	
	return(0);										//	return default
	
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
			\r1. shered memory id\n			\
			\r2. time for timer\n			\
			\r3. size of data base\n");
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

