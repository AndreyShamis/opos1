#ifndef EX3A_SEC
#define EX3A_SEC



//================== Catch exit Handler =======================================
//	handler function to know when child is exited
void catch_chld(int num);

//=============================================================================
//	function which seting handler by default
void setHendlerOptions();

//=============================================================================
//	function which run in cycle while not ^D or user not put exit
//	this function get command from user convert string to array of
//	strings and call to function exec with array of string
void cycle();

#endif

