#!module.syntax
module eSwitch.pic16f1824.output;

use PIC16F1824.interface;

/* PWM1: RC5, Timer4*/
void pwm1_init(){
	/* 1. Disable the CCPx pin output driver by setting the associated TRIS bit. */
	TRISC[5] = 1;
	/* 2. Load the PRx register with the PWM period value. */
	PR4 = 0xFF;
	/* 3. Configure the CCP module for the PWM mode by loading the CCPxCON register with the appropriate values. */
		// CCP1M = 1100
		// DC1B = 00
		// P1M = 00
	CCP1CON = 0b00001100;
	/* 4. Load the CCPRxL register and the DCxBx bits of the CCPxCON register, with the PWM duty cycle value. */
	CCPR1L = 0; //Start with 0% duty cycle
	/* 5. Configure and start Timer2/4/6:
		* Select the Timer2/4/6 resource to be used	for PWM generation by setting the CxTSEL<1:0> bits in the CCPTMRSx register.*/
		// Select timer 4
	CCPTMRS0[0] = 1;
	CCPTMRS0[1] = 0;
	/*	* Clear the TMRxIF interrupt flag bit of the PIRx register. See Note below. */
	/*	* Configure the TxCKPS bits of the TxCON register with the Timer prescale value. 
		* Enable the Timer by setting the TMRxON bit of the TxCON register. */
	T4CON = 0b100;
	/* 6. Enable PWM output pin:
		* Wait until the Timer overflows and the TMRxIF bit of the PIRx register is set. See Note below.
		* Enable the CCPx pin output driver	*/
	TRISC[5] = 0;
}

void pwm1_setDuty(uint8 duty){
	CCPR1L = duty;
}

/* PWM2: RC3, Timer6*/
void pwm2_init(){
	/* 1. Disable the CCPx pin output driver by setting the associated TRIS bit. */
	TRISC[3] = 1;
	/* 2. Load the PRx register with the PWM period value. */
	PR6 = 0xFF;
	/* 3. Configure the CCP module for the PWM mode by loading the CCPxCON register with the appropriate values. */
		// CCP1M = 1100
		// DC1B = 00
		// P1M = 00
	CCP2CON = 0b00001100;
	/* 4. Load the CCPRxL register and the DCxBx bits of the CCPxCON register, with the PWM duty cycle value. */
	CCPR2L = 0; //Start with 0% duty cycle
	/* 5. Configure and start Timer2/4/6:
		* Select the Timer2/4/6 resource to be used	for PWM generation by setting the CxTSEL<1:0> bits in the CCPTMRSx register.*/
		// Select timer 6
	CCPTMRS0[2] = 0;
	CCPTMRS0[3] = 1;
	/*	* Clear the TMRxIF interrupt flag bit of the PIRx register. See Note below. */
	/*	* Configure the TxCKPS bits of the TxCON register with the Timer prescale value. 
		* Enable the Timer by setting the TMRxON bit of the TxCON register. */
	T6CON = 0b100;
	/* 6. Enable PWM output pin:
		* Wait until the Timer overflows and the TMRxIF bit of the PIRx register is set. See Note below.
		* Enable the CCPx pin output driver	*/
	TRISC[3] = 0;
}

void pwm2_setDuty(uint8 duty){
	CCPR2L = duty;
}