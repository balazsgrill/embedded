/*
 * test.i2c.master.c
 *
 *  Created on: 2015 márc. 4
 *      Author: balazs.grill
 */

#include <i2c.master.h>

void main(void) {
	i2c_init(255);

	while(1){
		i2c_start();
		i2c_send_address(0x55u, 0);
		i2c_send_data(0xFFu);
		i2c_stop();
	}
}

