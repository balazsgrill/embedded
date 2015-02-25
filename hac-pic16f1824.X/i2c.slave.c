#include <xc.h>


#include "i2c.slave.h"

/*
 * SSP1STAT mask to decide current state
 * binary 00101101
 */
#define I2C_STATE_MASK 0x2Du

/*
 * Address received for Read operation, data shall be put to buffer
 * S = 1, D_A = 0, R_W = 1 BF=dontcare
 * Mask b'00001100' or b'00001101'
 */
#define I2C_STATE_RD_ADDR1 0x0Cu
#define I2C_STATE_RD_ADDR2 0x0Du

/*
 * Address received for Write operation
 * S = 1, D_A = 0, R_W = 0, BF = 1
 * Mask b'00001001'
 */
#define I2C_STATE_WR_ADDR 0x09u

/*
 * Read operation, next byte shall be put into buffer
 * S = 1, D_A = 1, R_W = 1, BF = 0
 * Mask b'00101100'
 */
#define I2C_STATE_RD_DATA 0x2Cu

/*
 * Data byte was received for Write operation
 * S = 1, D_A = 1, R_W = 0, BF = 1
 * Mask b'00101001'
 */
#define I2C_STATE_WR_DATA 0x29u

static uint8 i2c_last_address;

void i2c_init(uint8 address){
    SSP1CON1bits.SSPM=0x06;     // I2C Slave mode, 7-bit address
    SSP1ADD = address;
    SSP1CON1bits.CKP=1;         // release Clock
    SSP1CON1bits.SSPEN=1;       // enable MSSP
    i2c_last_address = address;
}

/**
 * Safely put data to the SSPBUF. This operation will try to write data to the SSP1BUF until
 * it succeeds without a write collision
 * @param data
 */
static inline void i2c_doPutData(uint8 data){
    while(SSP1STATbits.BF);
    do{
        SSP1CON1bits_t.WCOL = 0;
        SSPBUF = data;
    }while(SSP1CON1bits_t.WCOL);
    SSP1CON1bits.CKP = 1; // release the clock
}

void i2c_check(){
    uint8 data;

    if (PIR1bits.SSP1IF){
        PIR1bits.SSP1IF = 0;

        switch(SSP1STAT & I2C_STATE_MASK){
            case I2C_STATE_RD_ADDR1:
            case I2C_STATE_RD_ADDR2:
                i2c_last_address = SSP1BUF;
                data = cbk_i2c_read(i2c_last_address);
                i2c_doPutData(data);
                break;
            case I2C_STATE_RD_DATA:
                data = cbk_i2c_read(i2c_last_address);
                i2c_doPutData(data);
                break;
            case I2C_STATE_WR_ADDR:
                i2c_last_address = SSP1BUF;
                break;
            case I2C_STATE_WR_DATA:
                data = SSP1BUF;
                cbk_i2c_write(i2c_last_address, data);
                break;
            default:
                /* Clear RW flag */
                SSP1STATbits.R_nW = 0;
                break;
        }
    }
}
