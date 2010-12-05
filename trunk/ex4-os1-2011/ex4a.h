#ifndef EX3A_SEC
#define EX3A_SEC

struct rusage u_rusage;		//	struct used for get times
int status ;				//	to know which status was exited

//================== Catch exit Handler =======================================
//	handler function to know when child is exited
void catch_chld(pid_t num);

//=============================================================================
//	function which seting handler by default
void setHendlerOptions();

//=============================================================================
//	function which run in cycle while not ^D or user not put exit
//	this function get command from user convert string to array of
//	strings and call to function exec with array of string
void cycle();

#endif

