/* 
 * File:   runtime.h
 * Author: balazs.grill
 *
 * Created on 2014. február 4., 14:35
 */

#ifndef RUNTIME_H
#define	RUNTIME_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mtypes.h"
    void main_process_message(uint8 id, uint8 data);
#define COM_MESSAGE_RECEIVE(id, data) main_process_message(id, data)

    void main_timer_trigger(uint8 id);
#define SCH_TIMER_TRIGGER(id) main_timer_trigger(id)


#ifdef	__cplusplus
}
#endif

#endif	/* RUNTIME_H */

