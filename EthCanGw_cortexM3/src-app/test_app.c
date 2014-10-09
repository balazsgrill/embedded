/*
 * test_app.c
 *
 *  Created on: 2014.09.23.
 *      Author: balazs.grill
 */

#include "test_app.h"
#include <lwip/udp.h>
#include <lwip/ip.h>
#include "display.h"

static struct udp_pcb* receive_pcb;
static struct udp_pcb* send_pcb;

static void test_app_receive(void *arg, struct udp_pcb *upcb,
        struct pbuf *p,
        ip_addr_t *addr,
        u16_t port){

	udp_connect(send_pcb, addr, port);
	udp_send(send_pcb, p);
}

void test_app_init(){
	receive_pcb = udp_new();
	send_pcb = udp_new();
	udp_bind(receive_pcb, IP_ADDR_ANY, 10000);
	udp_recv(receive_pcb, &test_app_receive, NULL);
}

void test_app_poll(){

}

