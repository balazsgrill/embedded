/* 
 * File:   scheduler.h
 * Author: balazs.grill
 *
 * Created on 2014. február 4., 15:06
 */

#ifndef SCHEDULER_H
#define	SCHEDULER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mtypes.h"
    
void sch_init();
void sch_step();
void sch_start(uint8 id, uint8 timer);


#ifdef	__cplusplus
}
#endif

#endif	/* SCHEDULER_H */

