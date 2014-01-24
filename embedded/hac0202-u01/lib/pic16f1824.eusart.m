module pic16f1824.eusart;

use PIC16F1824.interface;
use uart;

/* TXSTA */
const uint8 TX9D = 0;
const uint8 TRMT = 1;
const uint8 BRGH = 2;
const uint8 SENDB = 3;
const uint8 SYNC = 4;
const uint8 TXEN = 5;
const uint8 TX9 = 6;

/* RCSTA */
const uint8 CREN = 4;
const uint8 SPEN = 7;

/* PIR1 */
const uint8 TXIF = 4;
const uint8 RCIF = 5;

void uart_init(){
 
	/*
	 * Configure BRG
	 * 9600 bps assuming 4MHz clock
	 */
	TXSTA[BRGH] = 1; //BRGH
	BAUDCON[3] = 1;
	SPBRGL = 103;
	SPBRGH = 0;
	
	/* Enable EUSART */
	
	RCSTA[CREN] = 1;
	TXSTA[SYNC] = 0;
	RCSTA[SPEN] = 1;
	
	TXSTA[TXEN] = 1;
}

boolean uart_canSend(){
	return PIR1[TXIF];
}

void uart_send(uint8 data){
	TXREG = data;
}

boolean uart_canReceive(){
	return PIR1[RCIF];
}

uint8 uart_receive(){
	PIR1[RCIF] = 0;
	return RCREG;
}