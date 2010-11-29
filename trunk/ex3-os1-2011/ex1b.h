#ifndef EX1B_SEC
#define EX1B_SEC

					
struct rusage u_rusage;		//	struct used for get times
int status ;				//	to know which status was exited

int stoped_id	=	0;		//	to know which preccess is in background
int backgrdnd 	= 	0;		//	to know if we have some process in back

//================== Catch exit Handler =======================================
void catch_chld(pid_t num);

//=============================================================================
void catch_int(int num);

//=============================================================================
void catch_stop(int num);

//=============================================================================
void setHandler();

//=============================================================================
void setHendlerOptions();

//=============================================================================
void cycle();

#endif
