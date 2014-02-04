/* 
 * File:   actuator.h
 * Author: balazs.grill
 *
 * Created on 2014. február 4., 15:30
 */

#ifndef ACTUATOR_H
#define	ACTUATOR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mtypes.h"

    void actuator_init();
    void actuator_relay1_on();
    void actuator_relay1_off();
    void actuator_relay2_on();
    void actuator_relay2_off();
    void actuator_relay_drive_off();

    void actuator_pwm1(uint8 value);
    void actuator_pwm2(uint8 value);

#ifdef	__cplusplus
}
#endif

#endif	/* ACTUATOR_H */

