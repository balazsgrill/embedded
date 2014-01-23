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
			//loop while(!uart_canSend()){}
			// this might be necessary in the future, but the compiler does not support this
			uart_send(d);
		}
	}
}