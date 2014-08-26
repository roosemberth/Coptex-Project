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

#include "../../SCP-Include/SCP-Config.h"
#include "../HwPlatforms/I2C-Bus.h"
#include <eigen3/Eigen/Dense>
#include "Barometer.h"

using namespace HwCtrl;

bool IMU::Barometer::Barometer(I2C_Bus &I2C_Interface){
	BarometerI2CAddress = SCP_Barometer_I2CAddr;
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
