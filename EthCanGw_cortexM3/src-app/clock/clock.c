/*
 * clock.c
 *
 *  Created on: 2014.08.26.
 *      Author: balazs.grill
 */

#include "clock.h"

static uint32_t clock_now;

//*****************************************************************************
//
// The interrupt handler for the for Systick interrupt.
//
//*****************************************************************************
void
SysTickIntHandler(void)
{
    //
    // Update the Systick interrupt counter.
    //
	clock_now++;
}

void clock_setup(void){
	clock_now = 0u;

	//
	    // 1ms tick
	    SysTickPeriodSet(SysCtlClockGet() / 1000u);

	    //
	    // Enable interrupts to the processor.
	    //
	    IntMasterEnable();

	    //
	    // Enable the SysTick Interrupt.
	    //
	    SysTickIntEnable();

	    //
	    // Enable SysTick.
	    //
	    SysTickEnable();
}


uint32_t sys_now(void)
{
	return clock_now;
}
