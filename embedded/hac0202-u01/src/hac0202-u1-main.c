/*
 * File:   hac0202-u1-main.c
 * Author: balazs.grill
 *
 * Created on 2014. február 4., 8:17
 */


#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = ON    // Clock Out Enable (CLKOUT function is enabled on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

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

#define RELAY1_ON 1u
#define RELAY1_OFF 2u
#define RELAY2_ON 4u
#define RELAY2_OFF 8u

void main(void) {
    INTCON = 0;
    /* 2Mhz clock */
    OSCCON = 0b01100011;
    sch_init();
    actuator_init();
    uart_init();
    sch_start(TIMER_STATUS, STATUS_PERIOD);

    while(1){
        sch_step();
        com_receive();
        com_process();
        com_transmit();
    }
}

void main_process_message(uint8 id, uint8 data){
    switch(id){
        case RXMSG_RELAYCMD:
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
            actuator_pwm1(data);
        break;
        case RXMSG_PWM2:
            actuator_pwm2(data);
        break;
    }
}

void main_timer_trigger(uint8 id){
    switch(id){
        case TIMER_STATUS:
            com_sendMsg(TXMSG_ERRORS, com_errorCount);
            com_errorCount = 0u;
            sch_start(TIMER_STATUS, STATUS_PERIOD);
        break;
        case TIMER_RELAY_OFF:
            actuator_relay_drive_off();
        break;
    }
}

