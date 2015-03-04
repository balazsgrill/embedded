/* 
 * File:   i2c.slave.h
 * Author: balazs.grill
 *
 * Created on 2015. február 24., 13:06
 */

#ifndef I2C_SLAVE_H
#define	I2C_SLAVE_H

#include "mtypes.h"

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * Initialize MSSP as an I2C device
     * @param address
     */
    void i2c_init(uint8 address);

    /**
     * This function shall be called periodically to operate MSSP
     */
    void i2c_check();

    /**
     * Callback function which is called when a byte is requested from the device
     * by the master.
     * @param address
     * @return
     */
    extern uint8 cbk_i2c_read(uint8 address);

    /**
     * Callback function which is called when a byte is written by the master to
     * this device
     * @param address
     * @param data
     */
    extern void cbk_i2c_write(uint8 address, uint8 data);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_SLAVE_H */

