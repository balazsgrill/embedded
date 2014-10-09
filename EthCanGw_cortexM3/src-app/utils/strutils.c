/*
 * strutils.c
 *
 *  Created on: 2014 okt. 8
 *      Author: balazs.grill
 */

#include "strutils.h"

static void __reverse (char* start, char* end)
{
        char tmp;

        while (end > start)
        {
                tmp = *end;                                             /* save end of the string int tmp variable */
                *end-- = *start;                                /* write to the end of the string its beginning */
                *start++ = tmp;                         /* and write to the beginning stuff from tmp */
        }
}

int count_chars(char* buffer, int max){
	int result = 0;
	while((*buffer != '\0') && (result < max)){
		buffer++;
		result++;
	}
	return result;
}

int strcopy(char* from, char* to, int target){
	int trgindex = target;
	int srcindex = 0u;
	while(from[srcindex] != '\0'){
		to[trgindex] = from[srcindex];
		srcindex++;
		trgindex++;
	}
	to[trgindex] = '\0';
	return srcindex;
}

/*------------------------------------------------------------------------------
 function name: itoa
 description:           converts signed integer to an char array. Valid 'base' in [2;16].
                                                Only base == 10 values are treated as signed.
 parameters:            value for converting, the output buffer, conversion base
 returned value:        pointer to the output buffer
------------------------------------------------------------------------------*/
char* itoa (int value, char* buffer, int base)
{
        static const char digits [] = "0123456789ABCDEF";
        char* tmpBuffer = buffer;
        int sign = 0;
        int quot, rem;

        if ( (base >= 2) && (base <= 16) )                                      /* check if the base is valid */
        {
                if (base == 10 && (sign = value) <0)            /* check base & sign of value in the tmp copy */
                {
                        value = -value;
                }

                do                                                                              /* calculate quotient & reminder */
                {
                        quot = value / base;
                        rem = value % base;
                        *buffer ++ = digits[rem];                               /* append the reminder to the string */
                } while ((value = quot));

                if (sign < 0)                                                   /* if negative value add a sign */
                {
                        *buffer++ = '-';
                }

                __reverse(tmpBuffer, buffer - 1);               /* reverse the string */
        }

        *buffer = '\0';
        return tmpBuffer;
}
