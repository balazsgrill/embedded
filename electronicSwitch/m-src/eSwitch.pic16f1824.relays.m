#!module.syntax
module eSwitch.pic16f1824.relays;

use PIC16F1824.interface;

uint8 request = 0;

/*
RA2 on, RA4 off: Relay 1
RA5 on, RC4 off: Relay 2
*/

void relays_init(){
	//init output
	LATA[2] = 0;
	LATA[4] = 0;
	LATA[5] = 0;
	LATC[4] = 0;

	TRISA[2] = 0;
	TRISA[4] = 0;
	TRISA[5] = 0;
	TRISC[4] = 0;
	
	//init timer1
	
}

void relays_refresh(){
	LATA[2] = request[0];
	LATA[4] = request[1];
	LATA[5] = request[2];
	LATC[4] = request[3];

	request = 0;
}

void relay1_on(){
	request[0] = 1;
	request[1] = 0;
}

void relay1_off(){
	request[0] = 0;
	request[1] = 1;
}

void relay2_on(){
	request[2] = 1;
	request[3] = 0;
}

void relay2_off(){
	request[2] = 0;
	request[3] = 1;
}