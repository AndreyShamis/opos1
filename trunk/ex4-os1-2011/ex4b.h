#ifndef EX4B_SEC
#define EX4B_SEC

					
struct rusage u_rusage;		//	struct used for get times
int status ;				//	to know which status was exited

int stoped_id	=	0;		//	to know which preccess is in background
int backgrdnd 	= 	0;		//	to know if we have some process in back

//================== Catch exit Handler =======================================
//	handler function to know when child is exited
void catch_chld(pid_t num);

//=============================================================================
//	handler for SIGINT
void catch_int(int num);

//=============================================================================
//	handler for SIGTSTP
void catch_stop(int num);

//=============================================================================
//	function which seting handler by default
void setHandler();

//=============================================================================
//	function which seting handler by default but only for SIGCHLD
void setHendlerOptions();

//=============================================================================
//	function which run in cycle while not ^D or user not put exit
//	this function get command from user convert string to array of
//	strings and call to function exec with array of string
void cycle();

#endif
