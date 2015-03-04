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

extern void i2c_init(uint8 clockDiv);
extern void i2c_send_address(uint8 address, uint8 rw);
extern void i2c_send_data(uint8 data);
extern uint8 i2c_read_data(void);
extern void i2c_start(void);
extern void i2c_stop(void);
extern void i2c_ack(void);
extern void i2c_nak(void);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_MASTER_H */
