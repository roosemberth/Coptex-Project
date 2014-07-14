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

#ifndef BOARD_H 
#define BOARD_H

#include "boards/CoptexBoard/at91sam7x512/AT91SAM7X512.h"
#include "Config_file.h"

/// ---> Definitions

#define BOARD_NAME "CoptexBoard"
#define BOARD_MAINOSC 		  18432000 	// Frequency of the main oscillator.
#define BOARD_MCK 			  48000000 	// Master clock freq (when using board_lowlevel.c)
#define ADC_MAX_CK_10BIT 	   5000000 	// ADC clock frequency, at 10-bit resolution (in Hz)
#define ADC_MAX_CK_8BIT 	   8000000 	// ADC clock frequency, at 8-bit resolution (in Hz)
#define ADC_STARTUP_TIME_MAX 		20	// Startup time max, return from Idle mode (in µs)
#define ADC_TRACK_HOLD_TIME_MIN    600	// Track and hold Acquisition Time min (in ns)

/// Usb Device Constants
#define BOARD_USB_UDP
#define BOARD_USB_PULLUP_ALWAYSON
#define BOARD_USB_NUMENDPOINTS                  6
#define BOARD_USB_ENDPOINTS_MAXPACKETSIZE(i)    ((((i) == 4) || ((i) == 5)) ? 256 : (((i) == 0) ? 8 : 64))
#define BOARD_USB_ENDPOINTS_BANKS(i)            ((((i) == 0) || ((i) == 3)) ? 1 : 2)
#define BOARD_USB_BMATTRIBUTES                  USBConfigurationDescriptor_BUSPOWERED_NORWAKEUP


/// ---> PIO Definitions

/// List of all DBGU pin definitions. (0x18000000 Stands for PA27 & PA28
#define PINS_DBGU  {0x18000000, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

// -> 10-DOF (GY-90) Module Connections
// Digital Compass "Data Ready" Pin Flag			GPIO0 in Schematics
#define COMPASS_DATA_READY				{1 << 21, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}
// Accelerometer Programmable Interrupt				GPIO1 in Schematics
#define ACCELEROMETER_IRQ				{1 << 22, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}
// Gyroscope Programmable Interrupt					GPIO2 in Schematics
#define GYROSCOPE_IRQ					{1 << 20, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
// Barometric Sensor "Master Clear" (Active Low)	GPIO3 in Schematics
#define BAROMETER_MASTER_CLEAR			{1 << 19, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEGLITCH | PIO_PULLUP}
// Barometric Sensor "End Of Conversation"			GPIO4 in Schematics
#define BAROMETER_END_OF_CONVERSATION	{1 << 18, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}

#define GY_90_SENSOR_PINS COMPASS_DATA_READY, ACCELEROMETER_IRQ, GYROSCOPE_IRQ, BAROMETER_MASTER_CLEAR, BAROMETER_END_OF_CONVERSATION


// -> PCA9698 Control Lines
// ~Reset											GPIO5 in Schematics
#define PIN_MULTIPLEXER_RESET	{1 << 17, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
// ~Interruption (Something Changed)				GPIO6 in Schematics
#define PIN_MULTIPLEXER_IRQ		{1 << 16, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEGLITCH}
// ~Output Enable									GPIO7 in Schematics
#define PIN_MULTIPLEXER_ENABLE	{1 << 15, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}

#define PIN_MULTIPLEXER_PINS PIN_MULTIPLEXER_RESET, PIN_MULTIPLEXER_IRQ, PIN_MULTIPLEXER_ENABLE


// -> I2C (TWI) Bridge Control (PCA9517A)
// I2C BUS1 ENABLE									GPIO8 in Schematics
#define IC2_CONTROL_BUS1_ENABLE	{1 << 13, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
// I2C BUS2 ENABLE									GPIO9 in Schematics
#define I2C_CONTROL_BUS2_ENABLE {1 << 12, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}

#define I2C_CONTROL_PINS IC2_CONTROL_BUS1_ENABLE, I2C_CONTROL_BUS2_ENABLE


// -> SSC (SPI1) Interface (Used as GPIO)				GPIO0 in Schematics
#define GPIO_10		{1 << 21, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
#define GPIO_11		{1 << 22, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
#define GPIO_12		{1 << 23, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
#define GPIO_13		{1 << 24, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
#define GPIO_14		{1 << 25, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
#define GPIO_15		{1 << 26, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
#define USER_GPIOS GPIO_10, GPIO_11, GPIO_12, GPIO_13, GPIO_14, GPIO_15

#define GPIO_PINS GY_90_PINS, PCA9698_PINS, PCA9517A_PINS, USER_GPIOS


// -> WIZ610wi pin definitions.
// USART0 (WIZ610wi Auxiliar Interface) Serial Pins
#define WIZ610wi_RXD				{1 << 00, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define WIZ610wi_TXD				{1 << 01, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define WIZ610wi_RTS				{1 << 03, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define WIZ610wi_CTS				{1 << 04, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
// WIZ610wi HW TRIGGER
#define WIZ610wi_HW_TRIGGER_PIN		{1 << 02, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
// WIZ610wi Link Active (Active low)
#define WIZ610wi_LINK_ACTIVE_PIN 	{1 << 18, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_DEFAULT}
// WIZ610wi Serial Link Active (Active low)
#define WIZ610_SERIAL_ACTIVE_PIN 	{1 << 19, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_DEFAULT}

#define WIZ610wi_SERIAL_PINS WIZ610wi_RXD, WIZ610wi_TXD, WIZ610wi_RTS, WIZ610wi_CTS
#define WIZ610wi_PINS WIZ610wi_SERIAL_PINS, WIZ610wi_HW_TRIGGER_PIN, WIZ610wi_LINK_ACTIVE_PIN


// -> USART1 pin definitions.
#define USART1_RXD_PIN  {1 <<  5, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define USART1_TXD_PIN  {1 <<  6, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define USART1_SCK_PIN  {1 <<  7, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define USART1_RTS_PIN  {1 <<  8, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define USART1_CTS_PIN  {1 <<  9, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define USART1_DCD_PIN  {1 << 23, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
#define USART1_DTR_PIN  {1 << 25, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
#define USART1_DSR_PIN  {1 << 24, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
#define USART1_RI_PIN	{1 << 26, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}

#define USART1_PINS USART1_RXD_PIN, USART1_TXD_PIN, USART1_SCK_PIN, USART1_RTS_PIN, \
					USART1_CTS_PIN, USART1_DCD_PIN, USART1_DTR_PIN, USART1_DSR_PIN, USART1_RI_PIN


// -> Serial Peripheral Interface 1 pin definitions.
#define PIN_SPI1_MISO   {1 << 24, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}
#define PIN_SPI1_MOSI   {1 << 23, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}
#define PIN_SPI1_SPCK   {1 << 22, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}
#define PIN_SPI1_NPCS0  {1 << 21, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}
#define PIN_SPI1_NPCS1  {1 << 25, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}
#define PIN_SPI1_NPCS2  {1 << 26, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}

#define SPI1_PINS       PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK
#define SPI1_CS_PINS PIN_SPI1_NPCS0, PIN_SPI1_NPCS1, PIN_SPI1_NPCS2

#define SPI1_INTERFACE_PINS SPI1_PINS, SPI1_CS_PINS


/// PWMC pin definitions.
#define PIN_PWMC_PWM0  {1 << 27, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_PWMC_PWM1  {1 << 28, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_PWMC_PWM2  {1 << 29, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_PWMC_PWM3  {1 << 30, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
#define PWM_PINS PIN_PWMC_PWM0, PIN_PWMC_PWM1, PIN_PWMC_PWM2, PIN_PWMC_PWM3

// -> TWI pins definition.
#define PINS_TWI  {0x00000C00, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

// -> The PIN list of PIO for EMAC
#if defined(NO_PHY)
// (0x3FCFF = PB0-PB7 + PB10-17 "goo.gl/bAU2Ul" Note that PIOreg[0]=PB31 and PIOreg[31]=PB0);
//  Recall that In NO_PHY operation, we don't use those MDIO pins.
	#define BOARD_EMAC_PINS     	{0x3FCFF, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}

#else
	/// The power up reset latch PIO for PHY
	#define BOARD_EMAC_PIN_TEST 	{(1<<15), AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}
	#define BOARD_EMAC_PIN_RMII		{(1<<16), AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}
	// In Phy normal operation, we need MDIO Pins, so we must define emac pins with them! (0x3FFFF = PB0-PB17)
	#define BOARD_EMAC_PINS 		{0x3FFFF, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
	// We force the address
	//(1<<5) PHY addr 0, (1<<6) PHY addr 1, (1<<13) PHY addr 2, (1<<14) PHY addr 3, (1<<4) PHY addr 4
	#define BOARD_EMAC_PINS_PHYAD	{0x6050, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT},\
                              	 	{0x0020, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}
	#define BOARD_EMAC_PIN_10BT 	{(1<<17), AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}
	#define BOARD_EMAC_PIN_RPTR 	{(1<< 7), AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}
	/// The PIN Configure list for EMAC on power up reset (MII)
	#define BOARD_EMAC_RST_PINS BOARD_EMAC_PINS_PHYAD, BOARD_EMAC_PIN_TEST, \
								BOARD_EMAC_PIN_RMII, BOARD_EMAC_PIN_10BT, BOARD_EMAC_PIN_RPTR
#endif

//------------------------------------------------------------------------------
/// Indicates chip has an EFC.
#define BOARD_FLASH_EFC
/// Address of the IAP function in ROM.
#define BOARD_FLASH_IAP_ADDRESS         0x300008
//------------------------------------------------------------------------------

#endif //#ifndef BOARD_H
