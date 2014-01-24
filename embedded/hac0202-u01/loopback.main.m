module loopback.main;

use uart;
use ports;

global void main(){
	ports_init();

	var uint8 d;
	uart_init();
	loop{
		if (uart_canReceive()){
			d = uart_receive();
		}else{
			d = 0xFF;
		}
		
		if (uart_canSend()){
			uart_send(d);
			dbg_set();
		}else{
			dbg_clr();
		}
	}
}