#!module.syntax
module eSwitch.pic16f1824.main;

use eSwitch.pic16f1824.output;

global void main(){
	pwm1_init();
	pwm2_init();
	
	pwm1_setDuty(50);
	pwm2_setDuty(75);
	
	loop{
		
	}
}