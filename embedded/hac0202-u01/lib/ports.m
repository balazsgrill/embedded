module ports;

use PIC16F1824.interface;


/*
 * Initialize IO ports
 * RC4 : uart Tx
 * RC5 : uart Rx
 * RA2 : CCP3 (PWM1)
 * RC1 : CCP4 (PWM2)
 * RA5, RA4 : Relay 1
 * RC2, RC3 : Relay 2
 */
void ports_init(){
	INTCON = 0;
	OSCCON = 0b01101011;

	/* First make everything an input to avoid transients */
	TRISA = 0xFF;
	TRISC = 0xFF;
	WPUA = 0;

	ANSELA = 0;
	ANSELC = 0;
	
	APFCON0 = 0b00000000;
	APFCON1 = 0b00000000;
	TRISC[3] = 0;
	LATC[3] = 1;
}

void dbg_set(){
	LATC[3] = 1;
}

void dbg_clr(){
	LATC[3] = 0;
}

void toggle(){
	if (LATC[3]){
		LATC[3] = 0;
	}else{
		LATC[3] = 1;
	}
}