module loopback.main;

use uart;
use ports;

global void main(){
	ports_init();

	var uint8 d;
	var uint16 i;
	uart_init();
	i = 10000;
	loop{
		if (uart_canReceive()){
			d = uart_receive();
			//loop while(!uart_canSend()){}
			// this might be necessary in the future, but the compiler does not support this
			uart_send(d);
		}else{
			
			if (i > 0){
				i = i-1;
			}else{
				i = 10000;
				d = 1;
				uart_send(d);
			}
		}
		
	}
}