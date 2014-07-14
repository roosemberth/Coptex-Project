/*
 * Interfaces_Functions.h
 *
 *  Created on: Aug 14, 2013
 *      Author: Roosemberth Palacios
 */

#ifndef INTERFACES_CONFIGURE_H_
#define INTERFACES_CONFIGURE_H_

#define ABS(val)		((val>=0)*val)+(-(val<0)*val)
//define ISO7816_Fi[]	372, 372, 558, 744, 1116, 1488, 1860, 512, 768, 1024, 1536, 2048
//#define ISO7816_Di[]	  1,   2,   4,   8,   16,   32,   12,  20
#define PIN_PULLUP		1 << 0
#define PIN_PERIPH_A	1 << 1
#define PIN_PERIPH_B	1 << 2
#define PIN_FILTER		1 << 3
#define PIN_MULTIDRIVE	1 << 4
#define PIN_SET_INPUT	0 << 5
#define PIN_SET_OUTPUT	1 << 5
#define PIN_IRQ_ENABLE	1 << 6
#define PIN_DEF_VALUE_1	1 << 7
#define PIN_DEF_VALUE_0	0 << 7

#define TWI_MASTER_TX 0
#define TWI_MASTER_RX ~0

#include "Config_file.h"
#include "board.h"
#include "aic/aic.h"
#include "pmc/pmc.h"
#include "twi/twi.h"
#include "usart/usart.h"

typedef struct S_Interface_t{
	struct PERIPH_BASE *BASE;
	u32_t ID;
} Interface_t;

Interface_t US0_DEV 			= {(struct PERIPH_BASE *)AT91C_BASE_US0, AT91C_ID_US0};
Interface_t US1_DEV 			= {(struct PERIPH_BASE *)AT91C_BASE_US1, AT91C_ID_US1};
Interface_t TC0_DEV 			= {(struct PERIPH_BASE *)AT91C_BASE_TC0, AT91C_ID_TC0};
Interface_t TC1_DEV 			= {(struct PERIPH_BASE *)AT91C_BASE_TC1, AT91C_ID_TC1};
Interface_t TC2_DEV 			= {(struct PERIPH_BASE *)AT91C_BASE_TC2, AT91C_ID_TC2};
Interface_t TWI_DEV				= {(struct PERIPH_BASE *)AT91C_BASE_TWI, AT91C_ID_TWI};
Interface_t PIOB_DEV			= {(struct PERIPH_BASE *)AT91C_BASE_PIOB, AT91C_ID_PIOB};

unsigned char ConfigureDevice(Interface_t *Interface, u32_t Config, u32_t Speed, u32_t IRQ_Trigger, u32_t IRQ_Mode, void (*Interface_irq_handler)(void)){
	PMC_EnablePeripheral(Interface->ID);
	switch(Interface->ID){
	case AT91C_ID_FIQ:														// Interface is FIQ!
		printf("-ConfigureDevice - Attempt to Configure an FIQ as System Peripheral!");
		break;

	case AT91C_ID_SYS:														// Interface is SYS!
		if (*Interface_irq_handler != NULL || 0){
			((AT91S_SYS *)Interface->BASE)->AIC_IECR = IRQ_Trigger;
		}
		break;

	case AT91C_ID_PIOA: case AT91C_ID_PIOB:									// Interface is PIO!
		ConfigurePIO((AT91S_PIO *)Interface->BASE, Config, Speed);			///XXX: In ConfigurePIO function, Speed actually means Pins to Configure!
		if (*Interface_irq_handler != NULL){
			((AT91S_PIO *)Interface->BASE)->PIO_IER= IRQ_Trigger;
		}
		break;

	case AT91C_ID_SPI0: case AT91C_ID_SPI1:									// Interface is SPI!
//		SPI_Configure(Interface, Config, Speed, PERIPHERALS_CLOCK);			//XXX: SPI_Configure To Be Written		PRIORITY: MEDIUM
		if (*Interface_irq_handler != NULL){
			((AT91S_SPI *)Interface->BASE)->SPI_IER = IRQ_Trigger;
		}
		break;

	case AT91C_ID_US0: case AT91C_ID_US1:									// Interface is USART!
		printf("-USART configure - Configuring USART %d", Interface->ID==AT91C_ID_US0 ? 0 : 1);
		USART_Configure((AT91S_USART *)Interface->BASE, Config, Speed, PERIPHERALS_CLOCK);
		if (*Interface_irq_handler != NULL){
			((AT91S_USART *)Interface->BASE)->US_IER = IRQ_Trigger;
		}
		USART_SetTransmitterEnabled(((AT91S_USART *)Interface->BASE), 1);
		USART_SetReceiverEnabled(((AT91S_USART *)Interface->BASE), 1);
		break;

	case AT91C_ID_SSC:														// Interface is SSC!
//		SSC_Configure(Interface->BASE, Config, Speed, PERIPHERALS_CLOCK);	// XXX: SSC_Configure To Be Written		PRIORITY: LOW
		if (*Interface_irq_handler != NULL){
			((AT91S_SSC *)Interface->BASE)->SSC_IER = IRQ_Trigger;
		}
		break;

	case AT91C_ID_TWI:														// Interface is TWI!
//		TWI_Configure(Interface->BASE, Config, Speed, PERIPHERALS_CLOCK);	// XXX: SSC_Configure To Be Written		PRIORITY: HIGH	TWI_ConfigureMaster(Interface->BASE, Speed, PERIPHERALS_CLOCK);
		if (*Interface_irq_handler != NULL){
			((AT91S_TWI *)Interface->BASE)->TWI_IER = IRQ_Trigger;
		}
		break;

	case AT91C_ID_PWMC:														// Interface is PWM!
//		PWM_Configure(Interface->BASE, Config, Speed, PERIPHERALS_CLOCK);	// XXX: PWM_Configure To Be Written		PRIORITY: HIGH
		if (*Interface_irq_handler != NULL){
			((AT91S_PWMC *)Interface->BASE)->PWMC_IER = IRQ_Trigger;
		}
		break;

	case AT91C_ID_UDP:														// Interface is USB!
//		USB_Configure(Interface->BASE, Config, Speed, PERIPHERALS_CLOCK);	// XXX: USB_Configure To Be Written		PRIORITY: MEDIUM
		if (*Interface_irq_handler != NULL){
			((AT91S_UDP *)Interface->BASE)->UDP_IER = IRQ_Trigger;
		}
		break;

	case AT91C_ID_TC0: case AT91C_ID_TC1: case AT91C_ID_TC2:				// Interface is TC!
//		u32_t *div, *tcclks;
//	    TC_FindMckDivisor(Speed, PERIPHERALS_CLOCK, &div, &tcclks);
//	    TC_Configure(Interface->BASE, tcclks | Config);						// XXX: TC_Configure To Be Modified		PRIORITY: HIGH
//	    ((AT91S_TC *)Interface->BASE)->TC_RC = (PERIPHERALS_CLOCK / (2 * div));
		if (*Interface_irq_handler != NULL){
			((AT91S_TC *)Interface->BASE)->TC_IER = IRQ_Trigger;
		}
		TC_Start((AT91S_TC *)Interface->BASE);
		break;

	case AT91C_ID_CAN:														// Interface is CAN!
//		CAN_Configure(Interface->BASE, Config, Speed, PERIPHERALS_CLOCK);	// XXX: CAN_Configure To Be Written		PRIORITY: LOW
		if (*Interface_irq_handler != NULL){
			((AT91S_CAN *)Interface->BASE)->CAN_IER = IRQ_Trigger;
		}
		break;

	case AT91C_ID_EMAC:														// Interface is EMAC!
//		EMAC_Configure(Interface->BASE, Config, Speed, PERIPHERALS_CLOCK);	// XXX: EMAC_Configure To Be Written	PRIORITY: HIGH
		if (*Interface_irq_handler != NULL){
			((AT91S_EMAC *)Interface->BASE)->EMAC_IER = IRQ_Trigger;
		}
		break;

	case AT91C_ID_ADC:														// Interface is ADC!
//		ADC_Configure(Interface->BASE, Config, Speed, PERIPHERALS_CLOCK);	// XXX: ADC_Configure To Be Written		PRIORITY: HIGH
		if (*Interface_irq_handler != NULL){
			((AT91S_ADC *)Interface->BASE)->ADC_IER = IRQ_Trigger;
		}
		break;

	case AT91C_ID_IRQ0: case AT91C_ID_IRQ1:									// Interface is IRQ!
		printf("-ConfigureDevice - Attempt to Configure an IRQ as System Peripheral!");
		break;

	default:																// Unknown Interface!
		printf("-ConfigureDevice - Attempt to Configure an Undefined System Peripheral!");
		break;
	}
	return 0;
}

void ConfigureAIC(Interface_t *Interface, u32_t IRQ_Mode, void (*Interface_irq_handler)(void)){
	AIC_ConfigureIT(Interface->ID, IRQ_Mode, *Interface_irq_handler);
	AIC_EnableIT(Interface->ID);
}
void ConfigureUSART(AT91S_USART *usart, u32_t mode, u32_t irq, u32_t baudrate, u32_t clock){
	usart->US_CR = AT91C_US_RSTRX | AT91C_US_RSTTX | AT91C_US_RXDIS | AT91C_US_TXDIS | AT91C_US_RSTSTA;
	usart->US_IDR = ~0;
	usart->US_MR = mode;
    if ((mode & AT91C_US_CLKS_EXT) == 0){
    	printf("\n-USART- An USART has been set to the SCK Pin speed\n");
    } else {
    	if ((mode & (AT91C_US_SYNC|AT91C_US_USMODE_ISO7816_0|AT91C_US_USMODE_ISO7816_1)) == 0){
    		u16_t CD = clock /(8*(2-((mode & AT91C_US_OVER) == 0))*baudrate);
    	    usart->US_BRGR = CD;
    	    u32_t actual_baudrate = (clock /(8*(2-((mode & AT91C_US_OVER) == 0))*CD));
    	    if ((7>=(u8_t)(ABS(baudrate - actual_baudrate)*8)) && ((u8_t)(ABS(baudrate - actual_baudrate)*8)>=0)){
    	    	usart->US_BRGR |= (ABS(baudrate - actual_baudrate)*8)<<16;
    	    	actual_baudrate = (clock /(8*(2-((mode & AT91C_US_OVER) == 0))*(CD + ABS(baudrate - actual_baudrate))));
        	}
        	if (baudrate != actual_baudrate){
        		printf("\n-USART- Attempt to Configure an USART to %d BPS, But it was configured at %f BPS\n", baudrate, (float)(clock /(8*(2-((mode & AT91C_US_OVER) == 0))*(CD + ABS(baudrate - actual_baudrate)))));
        		printf("-USART- Error = %f \n\n", 1-1-((float)(baudrate/(clock /(8*(2-((mode & AT91C_US_OVER) == 0))*(CD + ABS(baudrate - actual_baudrate)))))));

        	}
    	} else if ((mode & (AT91C_US_SYNC|AT91C_US_USMODE_ISO7816_0|AT91C_US_USMODE_ISO7816_1)) == AT91C_US_SYNC){
    		usart->US_BRGR = (unsigned int)(clock/baudrate);
    		if (baudrate != (unsigned int)(usart->US_BRGR)){
    		    		printf("\n-USART- Attempt to Configure an USART to %d BPS, But it was configured at %f BPS\n", baudrate, (float)(clock /baudrate));
    		    		printf("-USART- Error = %f \n\n", 1-(((float)(baudrate/clock))/(clock/baudrate)));
    		}
    	} else if ((mode & (AT91C_US_USMODE_ISO7816_0|AT91C_US_USMODE_ISO7816_1))){
/*    		u16_t CD, FiDi;
    		for(int i,j; i<10; i++){ for(j=0; j<10; j++){					// XXX: To be programmed later								PRIORITY LOW

    		}}*/
    	}
    	usart->US_IER = irq;
    }
}
void ConfigurePIO(AT91S_PIO *pio, u32_t mode, u32_t pins){
	pio->PIO_IDR = pins;
	if (PIN_PERIPH_A & mode)	{pio->PIO_ASR   &= ~0 & pins; pio->PIO_PDR = ~0 & pins;}
	if (PIN_PERIPH_B & mode)	{pio->PIO_BSR   &= ~0 & pins; pio->PIO_PDR = ~0 & pins;}
	if (PIN_SET_INPUT & mode)	{pio->PIO_ODR   = ~0 & pins; pio->PIO_PER = ~0 & pins;}
	if (PIN_SET_OUTPUT & mode)	{pio->PIO_OER	= ~0 & pins; pio->PIO_PER = ~0 & pins;}
	if (PIN_PULLUP & mode)		{pio->PIO_PPUER = ~0 & pins;} else {pio->PIO_PPUDR = ~0 & pins;}
	if (PIN_DEF_VALUE_1 & mode)	{pio->PIO_SODR  = ~0 & pins;} else {pio->PIO_CODR  = ~0 & pins;}
	if (PIN_MULTIDRIVE & mode)	{pio->PIO_MDER  = ~0 & pins;} else {pio->PIO_MDDR  = ~0 & pins;}
	if (PIN_FILTER & mode)		{pio->PIO_IFER  = ~0 & pins;} else {pio->PIO_IFDR  = ~0 & pins;}
	if (PIN_IRQ_ENABLE & mode)	{pio->PIO_IER   = ~0 & pins;} else {pio->PIO_IDR   = ~0 & pins;}
}
void ConfigureTWI(AT91S_TWI *pio, u32_t mode, u32_t clock){
	printf("-TWI configure - Configuring TWI Interface");
	if (mode==TWI_MASTER_TX) {

	} else if (mode==TWI_MASTER_RX){

	} else{
		printf("-TWI configure - Bad Attempt to configure TWI interface!");
	}
}

#endif /* INTERFACES_CONFIGURE_H_ */
