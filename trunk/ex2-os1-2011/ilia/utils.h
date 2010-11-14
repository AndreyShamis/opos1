//                                Const cection
//=============================================================================
#define MAX_MENU_STR_LEN 5		//	max string len for menu
#define MAX_STR_LEN  	200		//	max string lentgh const
#define MIN_STR_LEN		2		//	min string lentgh name+space+id
#define NUMBER_PARAM	3		//	number of parameters needed
#define NUMBER_SONS		2		//	numbers of sons
#define MAX_FILE_NAME 	100		//	max len of file name

//	sort types
#define SORT_BY_ID		"id"	//	const for set type of sort needed
#define SORT_BY_NAME	"name"	//	const for set type of sort needed
//	files names
#define ID_FILE_NAME	"id.out"	//	file name for outputs id`s
#define NAME_FILE_NAME	"name.out"	//	file name for output names
//	file open types
#define FILE_READ		"r"		//	type of open file -	for read 
#define FILE_WRITE		"w"		//	type of open file - for write

//	function for exec
#define CAT_FILE		"cat"	//	function to read whith cat


//------------------ DEFINE ENUM SECTION --------------------------------------
#ifndef UTILS_SEC
#define UTILS_SEC

//================================= ENUM SECTION ==============================
enum{
	TRUE	=	1,				//	true for functions using
	FALSE	=	0,				//	false for functions using

	SERIES 	= 	1,
	RANDOM 	= 	2,

	SON1	=	1,
	SON2	=	2,
};

#endif
