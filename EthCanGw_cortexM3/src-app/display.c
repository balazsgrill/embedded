/*
 * display.c
 *
 *  Created on: 2014.08.27.
 *      Author: balazs.grill
 */

#include "display.h"
#include "inc/hw_types.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "grlib/grlib.h"
#include "drivers/formike128x128x16.h"
#include "clock/clock.h"
#include <utils/strutils.h>


static tContext sContext;

static uint32_t last_time;

static void display_draw();

static DisplayEntry *displayEntries[10];
static uint8_t numof_displayEntries;


/*------------------------------------------------------------------------------
 function name: __reverse
 description:           local function reversing order of a string
 parameters:            pointer to the beginning of a string, pointer to the end of a string
 returned value:        none
------------------------------------------------------------------------------*/

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

	 numof_displayEntries = 0u;
}

void display_addEntry(DisplayEntry *entry){
	displayEntries[numof_displayEntries] = entry;
	numof_displayEntries++;
}

static void display_draw(){
		char text[20];
	 tRectangle sRect;
	 short middle;
	 int row;
	 int i;
	 int l;

	 /* Clear all */
	 sRect.sXMin = 0;
	 sRect.sYMin = 15;
	 sRect.sXMax = GrContextDpyWidthGet(&sContext) - 1;
	 sRect.sYMax = GrContextDpyHeightGet(&sContext) - 1;
	 GrContextForegroundSet(&sContext, ClrBlack);
	 GrRectFill(&sContext, &sRect);

	 middle =  GrContextDpyWidthGet(&sContext) / 2;

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

	 GrContextFontSet(&sContext, &g_sFontFixed6x8);
	 (void)itoa(numof_displayEntries, text, 10);
	 GrStringDrawCentered(&sContext, text, -1, middle, 7, 0);

	 row = 16;
	 for (i=0;i<numof_displayEntries;i++){

		 GrStringDraw(&sContext, displayEntries[i]->label, -1, 2, row, 0);
		 displayEntries[i]->getValue(text);
		 l = count_chars(text, 20);
		 if (l > 8){
			 row += 10;
			 GrStringDraw(&sContext, text, -1, 10, row, 0);
		 }else{
			 GrStringDraw(&sContext, text, -1, middle, row, 0);
		 }

		 row += 10;
	 }

/*
		    GrStringDraw(&sContext, "Uptime (s)", -1, 2, 16, 0);
		    (void)itoa(last_time/1000, text, 10);
		    GrStringDraw(&sContext, text, -1, middle, 16, 0);

		    GrStringDraw(&sContext, "DHCP state", -1, 2, 26, 0);
		    (void)itoa(netif_default->dhcp->state, text, 10);
		    GrStringDraw(&sContext, text, -1, middle, 26, 0);

		    GrStringDraw(&sContext, "IP address", -1, 2, 36, 0);
		    for(i=0;i<4;i++){
		    	(void)itoa((netif_default->ip_addr.addr >> (i*8))&0xff, text, 10);
		    	if (i != 3){
		    		j = count_chars(text, 4);
		    		text[j] = '.';
		    		text[j+1] = '\0';
		    	}
		    	GrStringDraw(&sContext, text, -1, 8+(i*4*6), 46, 0);

		    }

		    (void)itoa(count, text, 10);
		    GrStringDraw(&sContext, text, -1, 2, 56, 0);

		    GrStringDraw(&sContext, "Error", -1, 2, 66, 0);
		    (void)itoa(error_flags, text, 10);
		    GrStringDraw(&sContext, text, -1, middle, 66, 0);
*/
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
