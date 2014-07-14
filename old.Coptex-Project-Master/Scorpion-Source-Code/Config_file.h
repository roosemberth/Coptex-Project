/* Old include_list.h File*/

#ifndef CONFIG_FILE_H

	/// Define Chip if not yet defined
	#ifndef at91sam7x512
		#define at91sam7x512
	#endif

	#include "board.h"

	#ifndef PERIPHERALS_CLOCK
		#define PERIPHERALS_CLOCK	BOARD_MCK
	#endif

	#define USART0		AT91C_BASE_US0
	#define USART1		AT91C_BASE_US1
	#define TC0			AT91C_BASE_TC0
	#define TC1			AT91C_BASE_TC1
	#define TC2			AT91C_BASE_TC2
	#define TWI			AT91C_BASE_TWI

	// Define The Standard OUT/ERR exit flux
	#define USART_STDOUT_OUT_FLUX USART1
	#define USART_STDERR_OUT_FLUX USART1

	/// Define NIC Always on
	#define BOARD_EMAC_POWER_ALWAYS_ON

	/// Define No Phy Operation
	#define NO_PHY

	/// XXX: Define Spoof Phy, in order to spoof a phy for an enternal MII (EMAC) Connection
	#define SPOOF_PHY
#endif /*CONFIG_FILE_H*/
