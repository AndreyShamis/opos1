/*
 * EX1 :: 
 * =============================================================
 * Writen by: Andrey Shamis, id: 321470882, login:andreysh
 *
 *  
 *  
 */

//------------------------- including section ---------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------------------  Const section ------------------------------------
//const int MAX_STR_LEN 5;

//------------------------------ Sort By NAME ---------------------------------
void sort_by_name()
{
	//int high;
	
	//high = sizeof(data);
	//printf("size: %d \n",high);
	printf("By name\n");

}

char *all_one_arr(int to, char *grades);


void sort_by_id();


char **create_Cell(char **data,int len)
{

	char **new_data = (char **)malloc(sizeof(char)*len);
	//int count;
	
	if(new_data == NULL)
		printf("Can`t allocate more memroy");
		
	printf("aa: %d",sizeof(char)*len);
	
	//for(count=0;count<len-1;count++)
	//{
		new_data = data;
	//}
	free(data);
	return(new_data);
	
}

//-------------------- ALLOCATE ** ARRAY --------------------------------------
// Function to allocate memory for pragram data
// geting lower and upped index to allocate
// returning new data
char **all_two_arr(int to, char **stud)
{
    char **new_stud = NULL;      // create new pointer-pointer

    new_stud = (char**)malloc(sizeof(char)*to) ;   // alloc memory

    if(new_stud == NULL)        // check if have memory
    {
        //cout << "Error: alloc one array\n";
        //exit(EXIT_FAILURE);     // if not go away
    	printf("Error ----- all\n");
    }

	int i;
	int x;

    for(i=0;i<to-1;i++)
    {
        //if(i < to-1)
        //{
            // start copy data from previous cellsd
            new_stud[i] = NULL; // set be NULL
            // try allocate more memory
            new_stud[i] = all_one_arr(strlen(stud[i])+1,stud[i]);
            // copy previous data
            
            // copy all rows from 2

            //free(stud[i]);                  // free memory

        //}
        //else
        //{
        //    new_stud[i] = NULL;                 // set be NULL
        //    // allocate more memory for new cells
        //    new_stud[i] = all_one_arr(,new_stud[i]);
            
        //}
	    
	    //free(stud);                 // global free memory
     }   
    return(new_stud);                           // retun the data

}

//---------------------- MEMORY ALLOCATE --------------------------------------
// allocate memory only for rows/
// function get upper index needed to allocate
// act it is for if use trying allocate new array
// return pointer to new data
char *all_one_arr(int to, char *grades)
{
    char *arr ;                          // pointer for new data

    arr = (char*)malloc(sizeof(char)*to);  // try get memory

    if(arr == NULL)                     // check if geting success
    {
        //cout << "Error: alloc one array\n"; // print error
        //exit(EXIT_FAILURE);                 // if not exit
    	printf("Error aloc 1");
    }

	int i;
    // start work whith data
    for(i=0;i<to;i++)
       	arr[i] = grades[i]; // copy old data
        
    // trying to delete old data
    //if(grades != NULL)
       //free(grades);        // deleting

    return(arr);                // returning

}

int getID(char *str);
int cmpName(char *name1,char *name2);
//--------------  Prototypes section ------------------------------------------

//------------------------- Main section --------------------------------------
int main(int argc, char *argv[])
{
	
	char key[5];		//	Variable for menu		// TODO
	//char buf[20];		//	Variable for In data	// TODO
	
	char data[10][20];
	
	char **datap;
	
	FILE *fRead;		//	Var for red file
	FILE *fWrite;		// 	Var for write file
		
	int ind=0;
	
	if(argc == 3 )
	{

		fRead = fopen(argv[1],"r");
		fWrite = fopen(argv[2],"w");
	
		if(fRead == NULL)
			printf("Can`t read file %s \n", argv[1]);
		else
			while(fgets(data[ind],20,fRead) != NULL)	// TODO CONST
			{
			
				ind++;
//				datap = create_Cell(datap,ind);
				datap = all_two_arr(ind,datap); 			
				//fputs(buf,data[ind]);
				printf("%s \n",data[ind-1]);	
				
				//printf("---- %d \n",getID(data[ind]));
				
				
			}
		
		
		fgets(key,4,stdin);			// TODO Const
	
		if(!strcmp(key,"name"))
			sort_by_name();
		else if(!strcmp(key,"id"))
			sort_by_id();
	
		printf("DATA %s \n", argv[1]);
		//return ;
	
		fclose(fRead);			// close readed file
		fclose(fWrite);			// close writed file
	
	}
	

	return(1);
}

//------------------------------ Sort By ID -----------------------------------
void sort_by_id()
{
	printf("By id\n");

}

int getID(char *str)
{
	int count;
	char id[strlen(str)];
	int result;
	
	for(count=0;count<strlen(str);count++)
	{
		if(str[count] == ' ')
		{
			strncpy(id,str,count+1);
			break;
		}
			
	}
	
	result= atoi(id);

	printf("%d \n",result);

	return(result);
}

int cmpName(char *name1,char *name2)
{
	int count;
	
	int name1_len;
	int name2_len;
	
	char name1_str[strlen(name1)];
	char name2_str[strlen(name2)];
	
	for(count=0;count<strlen(name1);count++)
	{
		if(name1_str[count] == ' ')
		{
			//strncpy(id,str,count+1);
			
			name1_len = count-1;
			strncpy(name1_str,name1,count-1);

			break;
		}
			
	}
	
	
	for(count=0;count<strlen(name2);count++)
	{
		if(name2_str[count] == ' ')
		{
			//strncpy(id,str,count+1);
			strncpy(name1_str,name1,count-1);
			
			name2_len = count-1;
			break;
		}
			
	}
	
	if(strcmp(name1_str,name2_str))
	{
		printf("%s \n",name1_str);
		printf("%s \n",name2_str);
		return(1);
	}
	else
	{
		printf("%s \n",name2_str);
		printf("%s \n",name1_str);
		return(0);
	}

	
}

