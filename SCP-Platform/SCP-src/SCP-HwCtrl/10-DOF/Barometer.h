/*
 * "BMP085 Digital pressure sensor" - Coptex Project Hardware Control
 *
 * Copyright (C) 2013-2015 Roosemberth Palacios <roosemberth@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2.
 *
 *
 * Description:
 *
 * The BMP085 is a new generation of high precision digital pressure sensors
 * for consumer applications. The BMP085 is based on piezo-resistive technology
 * for EMC robustness, high accuracy and linearity as well as long term stability.
 * The ultra-low power, low voltage electronics of the BMP085 is optimized for
 * use in mobile phones, PDAs, GPS navigation devices and outdoor equipment. With
 * a low altitude noise of merely 0.25m at fast conversion time, the BMP085 offers
 * superior performance. The I2C interface allows for easy system integration with
 * a microcontroller.
 */

#ifndef SCP_HwCtrl__10DOF__Barometer_h
#define SCP_HwCtrl__10DOF__Barometer_h

#include "../../SCP-Include/SCP-Config.h"
#include "../HwPlatforms/I2C-Bus.h"
#include <eigen3/Eigen/Dense>
#include "IMU.h"
#include <math.h>
#include <ctype.h>

#define BMP085_

using namespace HwCtrl;

class IMU::Barometer{
	public:
		class C_BMP085{
			u8 AC1H;
			u8 AC1L;
			u8 AC2H;
			u8 AC2L;
			u8 AC3H;
			u8 AC3L;
			u8 AC4H;
			u8 AC4L;
			u8 AC5H;
			u8 AC5L;
			u8 AC6H;
			u8 AC6L;
			u8 B1H;
			u8 B1L;
			u8 B2H;
			u8 B2L;
			u8 MBH;
			u8 MBL;
			u8 MCH;
			u8 MCL;
			u8 MDH;
			u8 MDL;
			C_BMP085(){
				AC1H = 0xAA;
				AC1L = 0xAB;
				AC2H = 0xAC;
				AC2L = 0xAD;
				AC3H = 0xAE;
				AC3L = 0xAF;
				AC4H = 0xB0;
				AC4L = 0xB1;
				AC5H = 0xB2;
				AC5L = 0xB3;
				AC6H = 0xB4;
				AC6L = 0xB5;
				B1H = 0xB6;
				B1L = 0xB7;
				B2H = 0xB8;
				B2L = 0xB9;
				MBH = 0xBA;
				MBL = 0xBB;
				MCH = 0xBC;
				MCL = 0xBD;
				MDH = 0xBE;
				MDL = 0xBF;
			}
		} BMP085;
		Barometer(I2C_Bus &I2C_Interface, u8 Barometer_I2CAddress);
		bool UpdateData();
		char *SysStatus;
		long *SysPreassure;
		char *SysTemperature;
		bool config(void *ConfigPacket);
	private:
		u8 GPB1;
		u8 GPB2;
		u8 BarometerI2CAddress;
		I2C_Bus *IMU_Bus;
		short Temperature;
		long Preassure;

		// Calibration Values:
		int AC1;
		int AC2;
		int AC3;
		uint AC4;
		uint AC5;
		uint AC6;
		int B1;
		int B2;
		int MB;
		int MC;
		int MD;

		long B5;
};

bool IMU::Barometer::Barometer(I2C_Bus &I2C_Interface, u8 Barometer_I2CAddress){
	BarometerI2CAddress = Barometer_I2CAddress;
	IMU_Bus = I2C_Interface;
	Preassure = 0;
	Temperature = 0;
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.AC1H, &GPB1, 1)) return true;
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.AC1L, &GPB2, 1)) return true;
	AC1 = ((int) ((GPB1<<8) | GPB2));
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.AC2H, &GPB1, 1)) return true;
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.AC2L, &GPB2, 1)) return true;
	AC2 = ((int) ((GPB1<<8) | GPB2));
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.AC3H, &GPB1, 1)) return true;
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.AC3L, &GPB2, 1)) return true;
	AC3 = ((int) ((GPB1<<8) | GPB2));
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.AC4H, &GPB1, 1)) return true;
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.AC4L, &GPB2, 1)) return true;
	AC4 = ((int) ((GPB1<<8) | GPB2));
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.AC5H, &GPB1, 1)) return true;
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.AC5L, &GPB2, 1)) return true;
	AC5 = ((int) ((GPB1<<8) | GPB2));
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.AC6H, &GPB1, 1)) return true;
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.AC6L, &GPB2, 1)) return true;
	AC6 = ((int) ((GPB1<<8) | GPB2));
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.B1H, &GPB1, 1)) return true;
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.B1L, &GPB2, 1)) return true;
	B1 = ((int) ((GPB1<<8) | GPB2));
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.B2H, &GPB1, 1)) return true;
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.B2L, &GPB2, 1)) return true;
	B2 = ((int) ((GPB2<<8) | GPB2));
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.MBH, &GPB1, 1)) return true;
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.MBL, &GPB2, 1)) return true;
	MB = ((int) ((GPB1<<8) | GPB2));
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.MCH, &GPB1, 1)) return true;
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.MCL, &GPB2, 1)) return true;
	MC = ((int) ((GPB1<<8) | GPB2));
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.MDH, &GPB1, 1)) return true;
	if (IMU_Bus->Read(BarometerI2CAddress, BMP085.MDL, &GPB2, 1)) return true;
	MD = ((int) ((GPB1<<8) | GPB2));
	return false;
}

// TODO:[Critical] Implementation Pending!


#endif	// #ifndef SCP_HwCtrl__10DOF__Barometer_h
