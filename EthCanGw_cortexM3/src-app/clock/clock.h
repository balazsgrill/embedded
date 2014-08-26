/*
 * clock.h
 *
 *  Created on: 2014.08.26.
 *      Author: balazs.grill
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <lwip/sys.h>

extern void clock_setup(void);
extern void SysTickIntHandler(void);

#endif /* CLOCK_H_ */
