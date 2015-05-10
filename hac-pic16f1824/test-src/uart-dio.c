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
#pragma config CLKOUTEN = OFF    // Clock Out Enable (CLKOUT function is enabled on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

#include <uart.h>

/*
 * Pinout:
 * Rx: RC5
 * Tx: RC4
 * 
 * Free on RA: RA2, RA4, RA5
 * Free on RC: RC0, RC1, RC2, RC3
 * 
 * 8-bit control frame:
 * 4-bit command (lower), 4-bit arg (upper)
 * 
 * Command opcode: 
 * 0: Set TRISA (1 = input, 0 = output)
 * 1: Set TRISC (1 = input, 0 = output)
 * 2: OR LATA
 * 3: OR LATC
 * 4: AND LATA
 * 5: AND LATC
 * 6: SET LATA
 * 7: SET LATC
 * 8: XOR LATA
 * 9: XOR LATC  
 * 13: Read255
 * 14: Read
 * 15: NOP
 * 
 * From device to host:
 * Port data:
 *  lower 4-bit: PORTA
 *  upper 4-bit: PORTC                        
 */

// PORTA is 3-bits wide only (RA3 left out)
#define PORTA_MASK 0x37u
#define PORTC_MASK 0x0Fu

uint8 maskedSet(uint8 value, uint8 mask, uint8 bits){
  uint8 result = value;
  
  // Clear bits, that are 0 in bits
  result &= (~mask) | bits; 
  // Set bits that are 1 in bits
  result |= mask & bits;
  return result;
}

void main(void) {
    INTCON = 0;
    /* 2Mhz clock */
    OSCCON = 0b01100011;
    /* For EUSART, Tx/Rx pins shall be configured as input */
    TRISA = 0xFF;
    TRISC = 0xFF;
    WPUA = 0;
    LATA = 0;
    LATC = 0;

    ANSELA = 0;
    ANSELC = 0;
    APFCON0 = 0b00000000;
    APFCON1 = 0b00000000;

	uart_init();

  uint8 data = 0;
  uint8 l1;
  uint8 read = 0;

	while(1){
	   if (uart_canReceive()){
        data = uart_receive();
        if ((data & 1u) == 0u){
          // PORTA
          l1 = (data & 0xf0u) >> 2;
        }else{
          l1 = (data & 0xf0u) >> 4;
          // PORTC
        }
        switch(data & 0xfu){
        case 0:
           // Set TRISA
           TRISA = maskedSet(TRISA, PORTA_MASK, l1);
           break;
        case 1:
           // Set TRISC
           TRISC = maskedSet(TRISC, PORTC_MASK, l1);
           break;
        case 2: 
          // OR LATA
          LATA |= l1 & PORTA_MASK;  
          break;
        case 3:
          // OR LATC
          LATC |= l1 & PORTC_MASK;
          break;
        case 4:
          // AND LATA
          LATA &= l1 | (~PORTA_MASK);
          break;
        case 5:
          // AND LATC
          LATC &= l1 | (~PORTC_MASK);
          break;
        case 6:
          // SET LATA
          LATA = maskedSet(LATA, PORTA_MASK, l1);
          break;
        case 7:
          // SET LATC
          LATC = maskedSet(LATC, PORTC_MASK, l1);
          break;          
        case 8: 
          // XOR LATA
          LATA ^= l1 & PORTA_MASK;  
          break;
        case 9:
          // XOR LATC
          LATC ^= l1 & PORTC_MASK;
          break;
        case 13:
          read=255;
          break;
        case 14:
          read++;
          break;
        }
     }	
     if (uart_canSend()){
    	if ((read > 0u)){
    		/* PORTA 2-5 and  PORTC 0-3*/
    		data = ((PORTA>>2u) & 0xFu) | ((PORTC & 0xFu) << 4u);
    		uart_send(data);
    		read--;
    	}else{
    		// TODO send something for test purposes
    		//uart_send(0xFFu);
    	}
     }
	}


}

