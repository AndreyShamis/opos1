#ifndef EX1A_SEC
#define EX1A_SEC
struct rusage u_rusage;
int status ;
int grp_id;


//================== Catch exit Handler =======================================
void catch_chld(pid_t num);

//=============================================================================
void setHendlerOptions();

//=============================================================================
void cycle();

#endif

