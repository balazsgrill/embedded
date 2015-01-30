/*
 * File:   i2c.master.h
 * Author: balazs.grill
 *
 * Created on 2014. február 4., 8:49
 */

#ifndef I2C_MASTER_H
#define	I2C_MASTER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mtypes.h"

void i2c_init();
void i2c_work();
boolean i2c_canSend();
void i2c_send(uint8 data);
boolean i2c_canReceive();
uint8 i2c_receive();

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_MASTER_H */
