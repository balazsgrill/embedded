/*
 * display.c
 *
 *  Created on: 2014.08.27.
 *      Author: balazs.grill
 */

#include "inc/hw_types.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "grlib/grlib.h"
#include "drivers/formike128x128x16.h"
#include "clock/clock.h"

static tContext sContext;

static uint32_t last_time;

static void display_draw();

/*------------------------------------------------------------------------------
 function name: __reverse
 description:           local function reversing order of a string
 parameters:            pointer to the beginning of a string, pointer to the end of a string
 returned value:        none
------------------------------------------------------------------------------*/

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

void display_init(){
	 //
	 // Initialize the display driver.
	 //
	 Formike128x128x16Init();

	 //
	 // Turn on the backlight.
	 //
	 Formike128x128x16BacklightOn();

	 //
	 // Initialize the graphics context.
	 //
	 GrContextInit(&sContext, &g_sFormike128x128x16);

	 display_draw();

	 last_time = sys_now();
}

static void display_draw(){
		char text[20];
	 tRectangle sRect;

	 (void)itoa(last_time, text, 10);

		    //
		    // Fill the top 15 rows of the screen with blue to create the banner.
		    //
		    sRect.sXMin = 0;
		    sRect.sYMin = 0;
		    sRect.sXMax = GrContextDpyWidthGet(&sContext) - 1;
		    sRect.sYMax = 14;
		    GrContextForegroundSet(&sContext, ClrDarkBlue);
		    GrRectFill(&sContext, &sRect);

		    //
		    // Put a white box around the banner.
		    //
		    GrContextForegroundSet(&sContext, ClrWhite);
		    GrRectDraw(&sContext, &sRect);

		    //
		    // Put the application name in the middle of the banner.
		    //
		    GrContextFontSet(&sContext, &g_sFontFixed6x8);
		    GrStringDrawCentered(&sContext, "lwip", -1,
		                         GrContextDpyWidthGet(&sContext) / 2, 7, 0);

		    //
		    // Say hello using the Computer Modern 20 point font.
		    //
		    GrContextFontSet(&sContext, &g_sFontCm20);
		    GrStringDrawCentered(&sContext, text, -1,
		                         GrContextDpyWidthGet(&sContext) / 2,
		                         ((GrContextDpyHeightGet(&sContext) - 16) / 2) + 16,
		                         0);

		    //
		    // Flush any cached drawing operations.
		    //
		    GrFlush(&sContext);
}

void display_refresh(){
	uint32_t time = sys_now();

	if ((time-last_time) > 1000){
		last_time = time;
		display_draw();
	}
}
