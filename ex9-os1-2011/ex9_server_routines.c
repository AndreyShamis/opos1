
#include <stdio.h>						//	stdio include
#include <string.h> 					//	need for strlen
#include "/usr/include/rpc/rpc.h"		//	rpc include
#include <time.h>						//	need for srand time
#include "ex9_server.h"					//	server include

//=============================================================================
#define ID_CORRECT_LEN 9				//	corretc len of id
#define INFLUENCE_DIVIDER 2				//	to set nfluense
#define NUMBER_OF_POINTS 10000			//	total number of points
#define QUARTER_OF_CIRCLE 4				//	quarter of circle
#define DECIMAL_DEVIDER 10				//	didvider in id check
#define SMAL_DIGIT 0					//	smallest digit in id
#define BIG_DIGIT 9						//	biger digit in id

//=============================================================================
//	Function which get string and it is must be id wich gonna be checked if
//	it is correct id by checking CHECK DIGIT
//	return 1 if the string is correct id
//	and return 0 if incorrect id
int *is_valid_id_1(char **str,CLIENT *cl)
{
	static int result;					//	result be retuned
	
	int str_len = strlen(*str);			//	lentgh of string
	int counter = 0;					//	counter for for
	int sum = 0;						//	sum of all digits
	int res = 0;						//	for inside result
	int influence=0;					//	influence on digit
	int digit=0;						//	temporary digit
	
	result = 0;
	
	if(str_len == ID_CORRECT_LEN)
	{
		//	for all digit in string
		for(counter=0;counter<str_len;counter++)
		{
			//	math influence for digit
			influence = counter%INFLUENCE_DIVIDER + 1;
			//	get special digit
			digit = (int)((*str)[counter]) - '0';
			
			//	check if the digit in [0-9]
			if(digit < SMAL_DIGIT || digit > BIG_DIGIT)				
				break;
	
			//	multiplie the digit value in influence
			res= influence*digit;
			
			//	check if the value bigger than 9
			if(res>ID_CORRECT_LEN)
				res-=ID_CORRECT_LEN;
			
			sum+=res;							//	add to total sum
		
		}
		//	check if sum is good by checking check digit
		if(sum % DECIMAL_DEVIDER == 0)
			result = 1;							//	thats good id
		
	}
	
	return(&result);							//	return value
}

//=============================================================================
//	function to calculate Pi .geting multiplayer
//	return claculated value
double *estimate_pi_1(int *input,CLIENT *cl)
{
	static double result;					// value be returned
	const int multiplier = *input;			// set multiplier
	double xVal,							// rndom x coordinate value.
		   yVal,							// rndom y coordinate value.
		   distance,						// distance of points.
		   totalPoints = multiplier * NUMBER_OF_POINTS,//total points number.
		   pointsIn 	= 0;
	int index;	// for Looping.

	srand(time(NULL));	// init random.

	// Loop thrugh all random points, and calculate num of point in the circel.
	for(index = 0; index < totalPoints; index ++)
	{
		xVal = (double) rand()/RAND_MAX;
		yVal = (double) rand()/RAND_MAX;

		// alculate num of point in the circel
		distance = (xVal * xVal) + (yVal * yVal);
		distance = distance * distance;

		if(distance <= 1)
			pointsIn ++;
	}

	// return pai propabilety value.
	result = QUARTER_OF_CIRCLE * (pointsIn / totalPoints);
	
	return(&result);
}
