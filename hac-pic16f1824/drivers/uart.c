#include <pic16f1824.h>
#include "uart.h"

void uart_init(){

	/*
	 * Configure BRG
	 * 9600 bps assuming 2MHz clock
	 */
	TXSTAbits.BRGH = 1;
	BAUDCONbits.BRG16 = 0;
	SPBRGL = 10;
	SPBRGH = 0;

	/* Enable EUSART */

	RCSTAbits.CREN = 1;
	TXSTAbits.SYNC = 0;
	RCSTAbits.SPEN = 1;

	TXSTAbits.TXEN = 1;
}

boolean uart_canSend(){
	return PIR1bits.TXIF;
}

void uart_send(uint8 data){
	TXREG = data;
}

boolean uart_canReceive(){
	return PIR1bits.RCIF;
}

uint8 uart_receive(){
	PIR1bits.RCIF = 0;
	return RCREG;
}
