/*
 * File:   i2c-conf.h
 * Author: balazs.grill
 *
 * Created on 2014. február 4., 8:49
 */

#ifndef I2C_CONF_H
#define	I2C_CONF_H

#ifdef	__cplusplus
extern "C" {
#endif

/* Master if defined, slave otherwise */
#define I2C_MASTER

/* Slave address */
#define I2C_ADDRESS 4u

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */
