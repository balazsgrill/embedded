#include "actuator.h"
#include <xc.h>

void actuator_init(){

    /* First make everything an input to avoid transients */
    TRISA = 0xFF;
    TRISC = 0xFF;
    WPUA = 0;

    ANSELA = 0;
    ANSELC = 0;
    APFCON0 = 0b00000000;
    APFCON1 = 0b00000000;

    LATA = 0;
    LATC = 0;
}
void actuator_relay1_on(){

}
void actuator_relay1_off(){

}
void actuator_relay2_on(){

}
void actuator_relay2_off(){

}
void actuator_relay_drive_off(){

}

void actuator_pwm1(uint8 value){

}
void actuator_pwm2(uint8 value){
    
}