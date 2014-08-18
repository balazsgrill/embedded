#include <xc.h>
#include "mtypes.h"

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
#pragma config CLKOUTEN = OFF    // Clock Out Enable (CLKOUT function is enabled on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

void pwm(uint16 value){
    CCPR4L = (value >> 2u) & 0xFFu;
    //CCP4CONbits.DC4B = (value >> 8u) & 0x3u;
}

/*
* Initialize IO ports
* RC1 : CCP4 (PWM)
* RC2 : AN6 (ADC)
*/
void init_ports(){

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

    /* CCP3/4 on timer 4 */
    CCPTMRS0 = 0b01010000;

    /* Set up CCP4 (Timer4) */
    CCP4CON = 0b00001111;
    pwm(0u);

    /* Set up Timer4 (disabled pre-/postscaler)*/
    PR4 = 0xFFu;
    T4CON = 0b00000100;

    /* Enabled PWM output */
    TRISCbits.TRISC1 = 0;

    /*** Configuring ADC ***/
    /* Port configuration */
    ANSELC = 0b100;
    /* Select channel AN6 */
    ADCON0bits.CHS = 0b110;
    /* Right justified, Fosc/32, Reference is Vss-Vdd */
    ADCON1 = 0b10100000;

    /* Enable */
    ADCON0bits.ADON = 1u;
}

uint16 measure(void){
	ADCON0bits.GO = 1u;
	while(ADCON0bits.GO);

	return ((uint16)ADRESH << 8u) + (uint16)ADRESL;
}

void main(void) {
    INTCON = 0;
    /* 2Mhz clock */
    OSCCON = 0b01100011;

    init_ports();

    while(1){
    	pwm(measure());
    }
}



