/* 
 * File:   i2c.h
 * Author: balazs.grill
 *
 * Created on 2014. február 4., 8:49
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mtypes.h"
#include <config/i2c-conf.h>

void i2c_init(uint8 address, uint8 mode);
void i2c_work();
boolean i2c_canSend();
void i2c_send(uint8 data);
boolean i2c_canReceive();
uint8 i2c_receive();

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

