#include "inc/hw_types.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include <lwip/inet.h>
#include <lwip/tcp.h>
#include <lwip/netif.h>
#include <lwip/init.h>
#include <lwip/stats.h>
#include <lwip/timers.h>
#include <lwip/dhcp.h>
#include <netif/etharp.h>

#include <netif/mchdrv.h>

#include <enc28j60.h>

#include "display.h"
#include "clock/clock.h"
#include "test_app.h"
#include <encdebug.h>

struct ip_addr mch_myip_addr = {0x0200a8c0UL}; /* 192.168.0.2 */
struct ip_addr gw_addr = {0x0100a8c0UL}, netmask = {0x000000ffUL}; /* 192.168.0.1 */

static struct netif mchdrv_netif;

static enc_device_t mchdrv_hw;

void main_getIpAddr(char* buffer){
	char section[5];
	int i, j;
	int l=0;
	for(i=0;i<4;i++){
		(void)itoa((netif_default->ip_addr.addr >> (i*8))&0xff, section, 10);
		if (i != 3){
			j = count_chars(section, 4);
			section[j] = '.';
			section[j+1] = '\0';
		}
		l+=strcopy(section, buffer, l);
	}
}

void main_getUpTime(char* buffer){
	(void)itoa(sys_now()/1000, buffer, 10);
}

static DisplayEntry display_ipAddr = {
		"ip",
		&main_getIpAddr
};

static DisplayEntry display_uptime = {
		"upTime (s)",
		&main_getUpTime
};

static uint32_t error_flags;

void main_getErrorFlags(char * buffer){
	(void)itoa(error_flags, buffer, 10);
}

static DisplayEntry display_errorFlags = {
		"Errors",
		&main_getErrorFlags
};

static int receivedNZBytes = 0;
static int lastByte = 0;

void enc_debug(int id, int data){
	if (id == 0){
		lastByte = data;
		if (data != 0){
			receivedNZBytes++;
		}
	}
}

void main_getDebug0(char * buffer){
	char num[10];
	int l;
	(void)itoa(receivedNZBytes, num, 10);
	l = strcopy(num, buffer, 0);
	buffer[l] = '/';
	buffer[l+1] = '\0';
	l++;
	(void)itoa(lastByte, num, 10);
	strcopy(num, buffer, l);
}

static DisplayEntry display_debug0 = {
		"Debug0",
		&main_getDebug0
};


void mch_net_init(void)
{
	error_flags = 0u;

    // Initialize LWIP
    lwip_init();

    mchdrv_netif.hwaddr_len = 6;
    /* demo mac address */
    mchdrv_netif.hwaddr[0] = 0;
    mchdrv_netif.hwaddr[1] = 1;
    mchdrv_netif.hwaddr[2] = 2;
    mchdrv_netif.hwaddr[3] = 3;
    mchdrv_netif.hwaddr[4] = 4;
    mchdrv_netif.hwaddr[5] = 5;

    error_flags |= mchdrv_init(&mchdrv_netif);

    // Add our netif to LWIP (netif_add calls our driver initialization function)
    if (netif_add(&mchdrv_netif, &mch_myip_addr, &netmask, &gw_addr, &mchdrv_hw,
                &mchdrv_init, ethernet_input) == NULL) {
        LWIP_ASSERT("mch_net_init: netif_add (mchdrv_init) failed\n", 0);
        error_flags |= 1u;
    }

    netif_set_default(&mchdrv_netif);
    netif_set_up(&mchdrv_netif);

    dhcp_start(&mchdrv_netif);
    test_app_init();
}

void mch_net_poll(void)
{
    mchdrv_poll(&mchdrv_netif);
}

int main(void)
{
	//
	    // Set the clocking to run directly from the crystal.
	    //
	    ROM_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
	                       SYSCTL_XTAL_8MHZ);

	clock_setup();
	display_init();
	display_addEntry(&display_uptime);
	display_addEntry(&display_ipAddr);
	display_addEntry(&display_errorFlags);
	display_addEntry(&display_debug0);
	display_refresh();

    mch_net_init();


    while (1) {
        mch_net_poll();
        sys_check_timeouts();
        display_refresh();
        test_app_poll();
    }
}
