module loopback.main;

use uart;
use ports;
use PIC16F1824.interface;

global void main(){
	ports_init();
	LATC[2] = 1;
	

	var uint8 d;
	uart_init();
	LATC[2] = 0;
	loop{
	//LATC[2] = 1;
		d = 0;
		if (uart_canReceive()){
			d = uart_receive();
			uart_send(d);
		}
	}
	
}