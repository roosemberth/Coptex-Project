/* ----------------------------------------------------------------------------
  *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

//-----------------------------------------------------------------------------
/// !Contents
///
/// The code can be roughly broken down as follows:
///    - Init EMAC driver structure
///    - If NO_PHY is not Defined: Init DM9161 driver (Testing Board without WIFI Module
///    - If SPOOF_PHY is Defined: Spoof PHY to External EMAC Response**
///    - Initialize uIP modules
///    - Set the IP address of this host
///    - Http Response
///    - Uip Process
///
/// Please refer to the list of functions in the #Overview# tab of this unit
/// for more detailed information.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//         Includes & Defines
//-----------------------------------------------------------------------------

#include "Config_file.h"
#include "uip.h"
#include "uip_arp.h"
#include "tapdev.h"
#include "timer.h"

#include "board.h"
#include "pio/pio.h"
#include "usart/usart.h"
#include "tc/tc.h"
#include "aic/aic.h"
#include "pmc/pmc.h"
#include "utility/trace.h"

#include "dbgu/dbgu.h"
#include "twi/twi.h"
#include "utility/math.h"
#include "utility/assert.h"
#include "utility/trace.h"
#include "drivers/async/async.h"
#include "drivers/twi/twid.h"
#include "Interfaces_Configure.h"

#include <string.h>
#include <stdio.h>

//         Local definitions
#define BUF ((struct uip_eth_hdr *)&uip_buf[0])			/// uIP buffer : The ETH header
#define USART_MAX_BPS			500						/// Maximum Bytes Per Second (BPS) rate that will be forced using the CTS pin.
#define USART_BUFFER_SIZE		1						/// Size of the receive buffer used by the PDC, in bytes.
void uip_log(char *m){TRACE_INFO("-uIP- %s\n\r", m);}	/// Global function for uIP to use to log
static void app_init(void){								/// Initialize the application
    printf("Coptex Project Init ... \n\r");
    httpd_init();
    #ifdef __DHCPC_H__
    	printf("P: DHCPC Init\n\r");
    	dhcpc_init(MacAddress.addr, 6);
	#endif
}
#ifdef __DHCPC_H__
	void dhcpc_configured(const struct dhcpc_state *s){	/// Function for uIP DHCPC to use, when is configured (*s to DHCP instance)
		u8_t * pAddr;

		printf("\n\r");
		printf("=== DHCP Configurations ===\n\r");
		pAddr = (u8_t *)s->ipaddr;
		printf("- IP     : %d.%d.%d.%d\n\r",
				pAddr[0], pAddr[1], pAddr[2], pAddr[3]);
		pAddr = (u8_t *)s->netmask;
		printf("- Mask   : %d.%d.%d.%d\n\r",
				pAddr[0], pAddr[1], pAddr[2], pAddr[3]);
		pAddr = (u8_t *)s->default_router;
		printf("- Gateway: %d.%d.%d.%d\n\r",
				pAddr[0], pAddr[1], pAddr[2], pAddr[3]);
		pAddr = (u8_t *)s->dnsaddr;
		printf("- DNS    : %d.%d.%d.%d\n\r",
				pAddr[0], pAddr[1], pAddr[2], pAddr[3]);
		printf("===========================\n\r\n");
		uip_sethostaddr(s->ipaddr);
		uip_setnetmask(s->netmask);
		uip_setdraddr(s->default_router);

		#ifdef __RESOLV_H__
			resolv_conf(s->dnsaddr);
		#else
			printf("DNS NOT enabled in the demo\n\r");
		#endif
	}
#endif /* __DHCPC_H__ */

//		Local variables

/// Pins to configure for the application.
const Pin pins[] = {PINS_DBGU, GY_90_SENSOR_PINS, PIN_MULTIPLEXER_PINS, I2C_CONTROL_PINS, WIZ610wi_PINS, \
					USART1_PINS, SPI1_INTERFACE_PINS, PWM_PINS, PINS_TWI, BOARD_EMAC_PINS};
volatile unsigned int bytesReceived = 0;				// Number of bytes received between two timer ticks.
unsigned char USART_pBuffer[USART_BUFFER_SIZE];			// Receive buffer.
char pString[24];										// String buffer.

//         Local functions
void ISR_Usart1(void)									// Interrupt handler for USART0. Increments the number of bytes received in the
{														// current second and starts another transfer if the desired bps has not been not met.
    unsigned int status = USART1->US_CSR;				// Read USART status
    if ((status & AT91C_US_RXBUFF) == AT91C_US_RXBUFF){	// Receive buffer is full
        bytesReceived += USART_BUFFER_SIZE;
        if (bytesReceived < USART_MAX_BPS){				// Restart transfer if BPS is not high enough
            USART_ReadBuffer(AT91C_BASE_US1, USART_pBuffer, USART_BUFFER_SIZE);
        }
        else {											// Otherwise disable interrupt
           USART1->US_IDR = AT91C_US_RXBUFF;
        }
    }
}

void ISR_Tc0(void)										// Interrupt handler for TC0. Displays the number of bytes received during the...
{														// ...last second and the total number of bytes received, then restarts a read...
    static unsigned int bytesTotal = 0;					// ...transfer on the USART if it was stopped.
    unsigned int status = AT91C_BASE_TC0->TC_SR;		// Read TC0 status
    if ((status & AT91C_TC_CPCS) == AT91C_TC_CPCS) {	// RC compare
        bytesTotal += bytesReceived;
        sprintf(pString, "Bps: %4u; Tot: %6u\r", bytesReceived, bytesTotal);
        USART_WriteBuffer(USART1, pString, sizeof(pString));
        bytesReceived = 0;
        if (USART1->US_RCR == 0) {						// Resume transfer if needed
           USART_ReadBuffer(USART1, USART_pBuffer, USART_BUFFER_SIZE);
           USART1->US_IER = AT91C_US_RXBUFF;
        }
    }
}
int main(void){											// Default main() function.
	PIO_Configure(pins, PIO_LISTSIZE(pins));			// Do initialization and process tasks.
	u32_t US0_Mode = AT91C_US_USMODE | AT91C_US_CLKS_CLOCK | AT91C_US_CHRL_8_BITS | AT91C_US_PAR_NONE | AT91C_US_NBSTOP_1_BIT | AT91C_US_CHMODE_NORMAL, \
		  US0_Speed = 115200, \
		  US0_IRQ_Mode = 0, \
		  US0_IRQ_Trig = AT91C_US_RXBUFF;
	u32_t TC0_Mode = AT91C_TC_CPCTRG, \
		  TC0_Speed = 1, \
		  TC0_IRQ_Mode = 0, \
		  TC0_IRQ_Trig = AT91C_TC_CPCS;
	u32_t TWI_Mode = 0, \
		  TWI_Speed = 400000, \
		  TWI_IRQ_Mode = 0, \
		  TWI_IRQ_Trig = 0;
	ConfigureDevice(&US0_DEV, US0_Mode, US0_Speed, US0_IRQ_Mode, US0_IRQ_Trig, &ISR_Usart1);// Configure USART0
	ConfigureDevice(&TC0_DEV, TC0_Mode, TC0_Speed, TC0_IRQ_Mode, TC0_IRQ_Trig, &ISR_Tc0);	// Configure TC0
	ConfigureDevice(&TWI_DEV, TWI_Mode, TWI_Speed, TWI_IRQ_Mode, TWI_IRQ_Trig, 0);			// Configure TWI

	USART_ReadBuffer(USART1, USART_pBuffer, USART_BUFFER_SIZE);					// Start receiving data and start timer

	uip_ipaddr_t ipaddr;
    struct timer periodic_timer, arp_timer;
    unsigned int i;

    // System devices initialize
    tapdev_init();
    clock_init();
    timer_set(&periodic_timer, CLOCK_SECOND / 2);
    timer_set(&arp_timer, CLOCK_SECOND * 10);

    // Init uIP
    uip_init();

#ifndef __DHCPC_H__
    // Set the IP address of this host
    uip_ipaddr(ipaddr, HostIpAddress[0], HostIpAddress[1],
                       HostIpAddress[2], HostIpAddress[3]);
    uip_sethostaddr(ipaddr);

    uip_ipaddr(ipaddr, RoutIpAddress[0], RoutIpAddress[1],
                       RoutIpAddress[2], RoutIpAddress[3]);
    uip_setdraddr(ipaddr);

    uip_ipaddr(ipaddr, NetMask[0], NetMask[1], NetMask[2], NetMask[3]);
    uip_setnetmask(ipaddr);
#else
    printf("P: DHCP Supported\n\r");
    uip_ipaddr(ipaddr, 0, 0, 0, 0);
    uip_sethostaddr(ipaddr);
    uip_ipaddr(ipaddr, 0, 0, 0, 0);
    uip_setdraddr(ipaddr);
    uip_ipaddr(ipaddr, 0, 0, 0, 0);
    uip_setnetmask(ipaddr);
#endif

    uip_setethaddr(MacAddress);

    app_init();
    while(1) {
        uip_len = tapdev_read();
        if(uip_len > 0) {
        	if(BUF->type == htons(UIP_ETHTYPE_IP)){
        		uip_arp_ipin();
                uip_input();
                /* If the above function invocation resulted in data that
                should be sent out on the network, the global variable
                uip_len is set to a value > 0. */
                if(uip_len > 0) {
                    uip_arp_out();
                    tapdev_send();
                }
            } else if(BUF->type == htons(UIP_ETHTYPE_ARP)) {
                uip_arp_arpin();
                /* If the above function invocation resulted in data that
                should be sent out on the network, the global variable
                uip_len is set to a value > 0. */
                if(uip_len > 0) {
                    tapdev_send();
                }
            }
        } else if(timer_expired(&periodic_timer)) {
            timer_reset(&periodic_timer);
            for(i = 0; i < UIP_CONNS; i++) {
                uip_periodic(i);
                /* If the above function invocation resulted in data that
                   should be sent out on the network, the global variable
                   uip_len is set to a value > 0. */
                if(uip_len > 0) {
                  uip_arp_out();
                  tapdev_send();
                }
            }
#if UIP_UDP
            for(i = 0; i < UIP_UDP_CONNS; i++) {
                uip_udp_periodic(i);
                /* If the above function invocation resulted in data that
                   should be sent out on the network, the global variable
                   uip_len is set to a value > 0. */
                if(uip_len > 0) {
                    uip_arp_out();
                    tapdev_send();
                }
            }
#endif /* UIP_UDP */
      
            /* Call the ARP timer function every 10 seconds. */
            if(timer_expired(&arp_timer)) {
                timer_reset(&arp_timer);
                uip_arp_timer();
            }
        }

        // Display Statistics
        if ( USART_IsDataAvailable((AT91S_USART *)AT91C_BASE_US1) ) {

            EmacStats    stats;

            //DBGU_GetChar();
            EMAC_GetStatistics(&stats, 1);
            printf("=== EMAC Statistics ===\n\r");
            printf(" .tx_packets = %d\n\r", stats.tx_packets);
            printf(" .tx_comp = %d\n\r", stats.tx_comp);
            printf(" .tx_errors = %d\n\r", stats.tx_errors);
            printf(" .collisions = %d\n\r", stats.collisions);
            printf(" .tx_exausts = %d\n\r", stats.tx_exausts);
            printf(" .tx_underruns = %d\n\r", stats.tx_underruns);
            printf(" .rx_packets = %d\n\r", stats.rx_packets);
            printf(" .rx_eof = %d\n\r", stats.rx_eof);
            printf(" .rx_ovrs = %d\n\r", stats.rx_ovrs);
            printf(" .rx_bnas = %d\n\r", stats.rx_bnas);
        }
    }

    return 0;
}
