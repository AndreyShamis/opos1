

// A function that get id from string that include mixed data (not only ids).
//-----------------------------------------------------------------------------
// Input: Pointer to string from tabel (type *char).
// Output: id (type int).
int getID(const char *str)
{
	int count,
		result;
		
	int len = strlen(str);
	
	for(count=0;count<len;count++)
		if(str[count] == ' ')
		{
			result = popID(str,count+1);
			break;
		}

	return(result);
}

// A function that locate and convert string of digits to integer.
//-----------------------------------------------------------------------------
// Input: Pointer to sting(type *char) and start point to locate digits
// (type int).
// Output: id (type int).
int popID(const char *str,const int start)
{
	int count,
		i=0;
	int len=strlen(str);

	char temp[MAX_STR_LEN];

	for(count=start;count<len;count++)
		if(isdigit(str[count]))
		{
			temp[i]=str[count];
			i++;
		}
		else
		{
			temp[i] = '\0';
			break;

		}

	return(atoi(temp));
}


//#############################################################################
//------------------------------ Sort By NAME ---------------------------------
void print_arr( char **data,const int size)
{
	int i=0;
	
	for(i=0;i<size;i++)
	{
		
		printf("%s.",data[i]);
		//printf("");
	}
	printf("\n============================================================\n");
}

void print_arr_t( char **data,const int size)
{
	int i=0,x=0;
	
	for(i=0;i<size;i++)
	{
		for(x=0;x<strlen(data[i]);x++)
		{	
			if(data[i][x] == ' ')
				printf("\r\t\t\t\t");
				
			printf("%c",data[i][x]);
			
		}
		printf("\n");
	}
	printf("\n============================================================\n");
}
//#############################################################################

