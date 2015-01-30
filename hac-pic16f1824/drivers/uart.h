/* 
 * File:   uart.h
 * Author: balazs.grill
 *
 * Created on 2014. február 4., 8:49
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mtypes.h"

void uart_init();
boolean uart_canSend();
void uart_send(uint8 data);
boolean uart_canReceive();
uint8 uart_receive();


#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

