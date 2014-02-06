/* 
 * File:   com.h
 * Author: balazs.grill
 *
 * Created on 2014. február 4., 10:07
 */

#ifndef COM_H
#define	COM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mtypes.h"

    extern uint8 com_errorCount;

void com_sendMsg(uint8 id, uint8 data);
void com_transmit();
void com_receive();
void com_process();


#ifdef	__cplusplus
}
#endif

#endif	/* COM_H */

