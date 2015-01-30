#include <pic16f1824.h>
#include "i2c.h"

void i2c_init(){
	/*
	 * Slave Address
	 * In master mode baudrate divider : SCL pin clock period = ((ADD<7:0> + 1) *4)/FOSC
	 */
	SSP1ADD = I2C_ADDRESS;

	/**
	 * 1 = Slew rate control disabled for standard speed mode (100 kHz and 1 MHz)
	 * 0 = Slew rate control enabled for high speed mode (400 kHz)
	 */
	SSP1STATbits.SMP = 0u;

	/**
	 * 1 = Enable input logic so that thresholds are compliant with SMbus specification
	 * 0 = Disable SMbus specific inputs
	 */
	SSP1STATbits.CKE = 0u;

	/**
	 * 1 = Enables the serial port and configures the SDA and SCL pins as the source of the serial port pins(3)
	 * 0 = Disables serial port and configures these pins as I/O port pins
	 */
	SSP1CON1bits.SSPEN = 1u;

	/**
	 * In I2 C Slave mode: SCL release control
	 * 1 = Enable clock
	 * 0 = Holds clock low (clock stretch). (Used to ensure data setup time.)
	 */
	SSP1CON1bits.CKP = 1u;

	/**
	 * SSPM<3:0>: Synchronous Serial Port Mode Select bits
	 * 0000 = SPI Master mode, clock = FOSC/4
	 * 0001 = SPI Master mode, clock = FOSC/16
	 * 0010 = SPI Master mode, clock = FOSC/64
	 * 0011 = SPI Master mode, clock = TMR2 output/2
	 * 0100 = SPI Slave mode, clock = SCK pin, SS pin control enabled
	 * 0101 = SPI Slave mode, clock = SCK pin, SS pin control disabled, SS can be used as I/O pin
	 * 0110 = I2C Slave mode, 7-bit address
	 * 0111 = I2C Slave mode, 10-bit address
	 * 1000 = I2C Master mode, clock = FOSC/(4 * (SSP1ADD+1))(4)
	 * 1001 = Reserved
	 * 1010 = SPI Master mode, clock = FOSC/(4 * (SSP1ADD+1))(5)
	 * 1011 = I2C firmware controlled Master mode (Slave idle)
	 * 1100 = Reserved
	 * 1101 = Reserved
	 * 1110 = I2C Slave mode, 7-bit address with Start and Stop bit interrupts enabled
	 * 1111 = I2C Slave mode, 10-bit address with Start and Stop bit interrupts enabled
	 */
#ifdef I2C_MASTER
		SSP1CON1bits.SSPM = 8u; // Master
#else
		SSP1CON1bits.SSPM = 14u; // Slave, 7 bit addressing
#endif
}


void i2c_work(){

#ifdef I2C_MASTER
#else
	/* Slave operation */
	/* Slave reception
	 *
1. Start bit detected.
2. S bit of SSP1STAT is set; SSP1IF is set if interrupt
on Start detect is enabled.
3. Matching address with R/W bit clear is received.
4. The slave pulls SDA low sending an ACK to the
master, and sets SSP1IF bit.
5. Software clears the SSP1IF bit.
6. Software reads received address from
SSP1BUF clearing the BF flag.
7. If SEN = 1; Slave software sets CKP bit to
release the SCL line.
8. The master clocks out a data byte.
9. Slave drives SDA low sending an ACK to the
master, and sets SSP1IF bit.
10. Software clears SSP1IF.
11. Software reads the received byte from
SSP1BUF clearing BF.
12. Steps 8-12 are repeated for all received bytes
from the Master.
13. Master sends Stop condition, setting P bit of
SSP1STAT, and the bus goes idle.
	 */

/* Slave transmission
 * 1. Master sends a Start condition on SDA and
SCL.
2. S bit of SSP1STAT is set; SSP1IF is set if interrupt
on Start detect is enabled.
3. Matching address with R/W bit set is received by
the Slave setting SSP1IF bit.
4. Slave hardware generates an ACK and sets
SSP1IF.
5. SSP1IF bit is cleared by user.
6. Software reads the received address from
SSP1BUF, clearing BF.
7. R/W is set so CKP was automatically cleared
after the ACK.
8. The slave software loads the transmit data into
SSP1BUF.
9. CKP bit is set releasing SCL, allowing the master
to clock the data out of the slave.
10. SSP1IF is set after the ACK response from the
master is loaded into the ACKSTAT register.
11. SSP1IF bit is cleared.
12. The slave software checks the ACKSTAT bit to
see if the master wants to clock out more data.
13. Steps 9-13 are repeated for each transmitted
byte.
14. If the master sends a not ACK; the clock is not
held, but SSP1IF is still set.
15. The master sends a Restart condition or a Stop.
16. The slave is no longer addressed.
 */

	/* Receive data */
	if (SSP1IF){ //Has data
		//Read SSP1BUF
	}
#endif

}
boolean i2c_canSend();
void i2c_send(uint8 data);
boolean i2c_canReceive();
uint8 i2c_receive();
