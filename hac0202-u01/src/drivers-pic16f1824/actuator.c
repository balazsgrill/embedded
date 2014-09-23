#include "actuator.h"
#include <xc.h>

/*
* Initialize IO ports
* RC4 : uart Tx
* RC5 : uart Rx
* RA2 : CCP3 (PWM1)
* RC1 : CCP4 (PWM2)
* RA5, RA4 : Relay 1
* RC2, RC3 : Relay 2
*/

void actuator_init(){

    /* First make everything an input to avoid transients */
    TRISA = 0xFF;
    TRISC = 0xFF;
    WPUA = 0;
    LATA = 0;
    LATC = 0;

    ANSELA = 0;
    ANSELC = 0;
    APFCON0 = 0b00000000;
    APFCON1 = 0b00000000;

    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC3 = 0;

    /* CCP3/4 on timer 4 */
    CCPTMRS0 = 0b01010000;

    /* Set up CCP3 (Timer2) */
    CCP3CON = 0b00001111;
    actuator_pwm1(0u);

    /* Set up CCP4 (Timer4) */
    CCP4CON = 0b00001111;
    actuator_pwm2(0u);

    /* Set up Timer4 (disabled pre-/postscaler)*/
    PR4 = 0xFFu;
    T4CON = 0b00000100;

    /* Enabled PWM output */
    TRISAbits.TRISA2 = 0;
    TRISCbits.TRISC1 = 0;
}
void actuator_relay1_on(){
    LATAbits.LATA4 = 1;
}
void actuator_relay1_off(){
    LATAbits.LATA5 = 1;
}
void actuator_relay2_on(){
    LATCbits.LATC2 = 1;
}
void actuator_relay2_off(){
    LATCbits.LATC3 = 1;
}
void actuator_relay_drive_off(){
    LATAbits.LATA4 = 0;
    LATAbits.LATA5 = 0;
    LATCbits.LATC2 = 0;
    LATCbits.LATC3 = 0;
}

void actuator_pwm1(uint8 value){
	CCPR3L = value;
	CCP3CONbits.DC3B = value & 0x3;

}
void actuator_pwm2(uint8 value){
    CCPR4L = value;
    CCP4CONbits.DC4B = value & 0x3;
}
