#include <application.h>
#include "runtime.h"
#include "mtypes.h"
#include "uart.h"
#include "com.h"
#include "runtime.h"
#include "scheduler.h"
#include "actuator.h"

#define TIMER_STATUS 0u
#define STATUS_PERIOD 30u

#define TIMER_RELAY_OFF 1u
#define RELAY_ON_PERIOD 1u

#define RXMSG_RELAYCMD 0u
#define RXMSG_PWM1 1u
#define RXMSG_PWM2 2u
#define TXMSG_ERRORS 0u
#define TXMSG_ACK 1u
#define TXMSG_UNKNOWN_MESSAGE 2u

#define RELAY1_ON 1u
#define RELAY1_OFF 2u
#define RELAY2_ON 4u
#define RELAY2_OFF 8u


void application_mainloop(){
    while(1){
        sch_step();
        com_receive();
        com_process();
        com_transmit();
    }
}

void application_init(){
	sch_init();
	actuator_init();
	uart_init();
	sch_start(TIMER_STATUS, STATUS_PERIOD);
}

void main_process_message(uint8 id, uint8 data){
bool ok = FALSE;
    switch(id){
        case RXMSG_RELAYCMD:
			ok = TRUE;
            if ((data & RELAY1_ON) != 0){
                actuator_relay1_on();
            }
            if ((data & RELAY1_OFF) != 0){
                actuator_relay1_off();
            }
            if ((data & RELAY2_ON) != 0){
                actuator_relay2_on();
            }
            if ((data & RELAY2_OFF) != 0){
                actuator_relay2_off();
            }
            sch_start(TIMER_RELAY_OFF, RELAY_ON_PERIOD);
        break;
        case RXMSG_PWM1:
			ok = TRUE;
            actuator_pwm1(data);
        break;
        case RXMSG_PWM2:
			ok = TRUE;
            actuator_pwm2(data);
        break;
    }
	if (ok){
		com_sendMsg(TXMSG_ACK, id);
	}else{
		com_sendMsg(TXMSG_UNKNOWN_MESSAGE, id);
	}
}

void main_timer_trigger(uint8 id){
    switch(id){
        case TIMER_STATUS:
			if (com_errorCount > 0u){
	    		com_sendMsg(TXMSG_ERRORS, com_errorCount);
        	    com_errorCount = 0u;
			}
            sch_start(TIMER_STATUS, STATUS_PERIOD);
        break;
        case TIMER_RELAY_OFF:
            actuator_relay_drive_off();
        break;
    }
}
