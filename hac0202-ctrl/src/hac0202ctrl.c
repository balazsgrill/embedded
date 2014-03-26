/*
 * hac0202ctrl.c
 *
 *  Created on: 2014.03.25.
 *      Author: balazs.grill
 */

#include <stdio.h>
#include <mcp2200.h>

#define RETURN_OK 0u
#define RETURN_INVALID_ARGS 1u
#define RETURN_SEND_FAIL 2u
#define RETURN_NO_DEVICE 3u
#define RETURN_TIMEOUT 4u
#define RETURN_NOT_OK 5u

#define MSGID_ACK 1
#define MSGID_UNKNOWN_MSG 2

static uint8_t calcCheck(uint8_t id, uint8_t data){
	uint8_t check = 0xFu;
    check -= (id + (data & 0xFu) + ((data & 0xF0u)>>4u));
    check = check & 0xFu;
	return check;
}

int connectAndSend(int id, int data){
	int cnt = mcp2200_list_devices(MCP2200_VENDOR_ID, MCP2200_PRODUCT_ID);
	if (cnt < 0) return cnt;

	if (cnt != 1) return RETURN_NO_DEVICE;

	int connectionID = mcp2200_connect(0);

	if (connectionID < 0){
		return connectionID;
	}

	int r = mcp2200_hid_configure(connectionID, 0, 0, 0, 0, 1249);
	if (r != 0){
		return r;
	}

	return send(connectionID, id, data);
}

int processMsg(uint8_t rcv[], int size, int expectedId, int* processed){
	int index = 0;
	while(size-index >= 2){

		/* check if we're looking at a valid message */
		uint8_t rcv_id = rcv[index] & 0xfu;
		uint8_t rcv_check = (rcv[index] & 0xf0u) >> 4u;
		uint8_t rcv_data = rcv[index+1];

		if (rcv_check == calcCheck(rcv_id, rcv_data)){
			index += 2;
			if (MSGID_ACK == rcv_id && expectedId == rcv_data){
				/* Received Ack message */
				return RETURN_OK;
			}
			if (MSGID_UNKNOWN_MSG == rcv_id && expectedId == rcv_data){
				/* Received "unknown message" message */
				return RETURN_SEND_FAIL;
			}
		}else{
			/* not a message, drop a byte */
			index++;
		}
	}
	/* No relevant messages received */
	*processed = index;
	return RETURN_NOT_OK;
}

int send(int connectionID, int id, int value){
	uint8_t data[2];

	int i;
	int j;
	int count;
	int start;
	uint8_t rcv_data[32];

	uint8_t check = calcCheck((uint8_t)id, (uint8_t)value);
	uint8_t h = (check << 4u) + (id & 0xFu);

	data[0] = h;
	data[1] = value;

	int r = mcp2200_send(connectionID, data, 2);
	if (r < 0) return r;

	start = 0;
	for(count=0;count<20;count++){
		r = mcp2200_receive(connectionID, &rcv_data[start], 32-start, &i);
		if (r == 0){
			r = processMsg(rcv_data, start+i, id, &j);
			if (r == RETURN_OK){
				return RETURN_OK;
			}else{
				if (r != RETURN_NOT_OK){
					return r;
				}
				int l;
				/* Copy unprocessed bytes to the beginning of the buffer */
				int remain = start+i-j;
				for(l=0;l<remain;l++){
					rcv_data[l] = rcv_data[j+l];
				}
				start = remain;
			}
		}
	}

	return RETURN_TIMEOUT;
}

int main(int argc, char** argv){

	if (argc != 3){
		return RETURN_INVALID_ARGS;
	}

	int id = 0;
	int data = 0;

	if (1 != sscanf(argv[1], "%d", &id)) return RETURN_INVALID_ARGS;
	if (1 != sscanf(argv[2], "%d", &data)) return RETURN_INVALID_ARGS;

	int r = mcp2200_init();
	if (r < 0){
		return r;
	}

	r = connectAndSend(id, data);
	mcp2200_close();

	return r;
}
