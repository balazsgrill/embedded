#include "i2c.master.h"

/**
 * I2C master driver
 *
 * Write scenario:
 * i2c_start();
 * i2c_send_address(address, 0);
 * i2c_send_data(data1);
 * i2c_send_data(data2);
 * i2c_stop();
 *
 * Read scenario:
 * i2c_start();
 * i2c_send_address(address, 1);
 * data1 = i2c_read_data();
 * i2c_nak();
 * i2c_stop();
 */

void i2c_init(uint8 clockDiv){
	SSP1CON1bits.SSPM=0x08;       // I2C Master mode, clock = Fosc/(4 * (SSPADD+1))
	SSP1ADD = clockdiv;
	SSP1CON1bits.SSPEN=1;         // enable MSSP
}

void i2c_send_address(uint8 address, uint8 rw){
    PIR1bits.SSP1IF=0;
    SSPBUF = (BlockAddress <<1) + (RW_bit & 1u);
    while(!PIR1bits.SSP1IF);
}

void i2c_send_data(uint8 data){
    PIR1bits.SSP1IF=0;
    SSPBUF = data;
    while(!PIR1bits.SSP1IF);
}

uint8 i2c_read_data(void){
    PIR1bits.SSP1IF=0;
    SSPCON2bits.RCEN=1;
    while(!PIR1bits.SSP1IF);
    return (SSPBUF);
}

void i2c_start(void){
    PIR1bits.SSP1IF=0;
    SSPCON2bits.SEN=1;
    while(!PIR1bits.SSP1IF);
}

void i2c_stop(void){
    PIR1bits.SSP1IF=0;
    SSPCON2bits.PEN=1;
    while(!PIR1bits.SSP1IF);
}

void i2c_ack(void){
   PIR1bits.SSP1IF=0;
   SSPCON2bits.ACKDT=0;
   SSPCON2bits.ACKEN=1;
   while(!PIR1bits.SSP1IF);
}

void i2c_nak(void){
    PIR1bits.SSP1IF=0;
    SSPCON2bits.ACKDT=1;
    SSPCON2bits.ACKEN=1;
    while(!PIR1bits.SSP1IF);
}
