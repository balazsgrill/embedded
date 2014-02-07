#include "com.h"
#include "uart.h"
#include "runtime.h"

#define TX_BUFFERSIZE 16

static uint8 txBuffer[TX_BUFFERSIZE];
static uint8 txstart = 0;
static uint8 txend = 0;

uint8 com_errorCount = 0;

static uint8 head = 0;
static uint8 data = 0;

/* States:
	0: no head, no data
	1: head arrived, no data
	2: head and data arrived
*/
static uint8 state = 0;

void com_sendMsg(uint8 id, uint8 data){
    uint8 check = 0xFu;
    check -= (id + (data & 0xFu) + ((data & 0xF0u)>>4u));
    check = check & 0xFu;
    uint8 h = (check << 4u) + (id & 0xFu);
    txBuffer[txend] = h;
    txend = (txend+1)%TX_BUFFERSIZE;
    txBuffer[txend] = data;
    txend = (txend+1)%TX_BUFFERSIZE;
}

void com_transmit(){
    if (txend != txstart){
        if (uart_canSend()){
            uint8 d = txBuffer[txstart];
            txstart = (txstart + 1) % TX_BUFFERSIZE;
            uart_send(d);
        }
    }
}

void com_receive(){
	if (uart_canReceive()){
		uint8 d = uart_receive();
		if (state == 0){
			head = d;
			state = 1;
		}else{
			data = d;
			state = 2;
		}
	}
}

void com_process(){
	if (state == 2){
		uint8 id = head & 0x0Fu;
		uint8 check = (head & 0xF0u) >> 4u;

		check = check + id + (data & 0xfu) + ((data) & 0xf0u >> 4u);

		if ((check & 0xF) == 0xF){
			/* Message is correct, process it */
			state = 0;
                        COM_MESSAGE_RECEIVE(id, data);
		}else{
			/* Incorrect message, drop first byte */
			head = data;
			state = 1;
                        com_errorCount++;
		}
	}
}

