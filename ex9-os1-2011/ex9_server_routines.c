#include <stdio.h>
#include <ctype.h>
#include <string.h> 				//	need for strlen
#include "/usr/include/rpc/rpc.h"
#include <time.h>					//	need for srand time
#include "ex9_server.h"

int *is_valid_id_1(char **str,CLIENT *cl)
{
	static int result;
	
	int str_len = strlen(*str);
	int i = 0;
	int sum = 0;
	int res = 0;	
	if(str_len != 9 && isdigit((*str)[8]))
		result = 0;
	else
	{
		for(i=0;i<str_len;i++)
		{
			int zz = i%2 + 1;
			int digit = (int)((*str)[i]) - '0';
			res=zz*digit;
			if(res>9)
				res-=9;
			sum+=res;
		
		}
		if(sum % 10 == 0)
			result = 1;	
		else
			result = 0;
	}
	
	return(&result);
}

double *estimate_pi_1(int *input,CLIENT *cl)
{
	static double result;					// value be returned
	const int multiplier = *input;			// set multiplier
	double xVal,							// rndom x coordinate value.
		   yVal,							// rndom y coordinate value.
		   distance,						// distance of points.
		   totalPoints 	= multiplier * 10000,// difine total points number.
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
	result = 4 * (pointsIn / totalPoints);
	
	return(&result);
}
