/*
 * "SCP Inertial Measurement Unit (IMU)" - Coptex Project Hardware Control
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
 * 10-DOF integrates four sensors including one sensor of 3-axis gyroscope
 * and 3-axis accelerometer(MPU6050), one magnetic field strength sensor(HMC5883L)
 * and a digital barometer sensor(BMP180). This module adopts I2C interface,
 * widely used in automation control.
 */

#ifndef SCP_HwCtrl__10_DOF__IMU_h
#define SCP_HwCtrl__10_DOF__IMU_h

#include "../HwPlatforms/I2C-Bus.h"
#include "Gyroscope.h"
#include "Accelerometer.h"
#include "Magnetometer.h"
#include "Barometer.h"

using namespace HwCtrl;

struct IMU_Addrs{
	u8 Gyroscope_I2CAddr;
	u8 Accelerometer_I2CAddr;
	u8 Magnetometer_I2CAddr;
	u8 Barometer_I2CAddr;
};

class IMU{
	public:
		class Gyroscope;
		class Accelerometer;
		class Magnetometer;
		class Barometer;
		IMU(I2C_Bus &I2C_Interface, struct IMU_Addrs);
		Gyroscope Gyroscope;
		Accelerometer Accelerometer;
		Magnetometer Magnetometer;
		Barometer Barometer;
	private:

};

IMU::IMU(I2C_Bus &I2C_Interface, struct IMU_Addrs DevicesAddresses){
	if (DevicesAddresses.Gyroscope_I2CAddr!=NULL || DevicesAddresses.Gyroscope_I2CAddr!=0){
		Gyroscope = new Gyroscope(I2C_Interface, DevicesAddresses.Gyroscope_I2CAddr);
	}
	if (DevicesAddresses.Accelerometer_I2CAddr!=NULL|| DevicesAddresses.Accelerometer_I2CAddr!=0){
		Accelerometer = new Accelerometer(I2C_Interface, DevicesAddresses.Accelerometer_I2CAddr);
	}
	if (DevicesAddresses.Magnetometer_I2CAddr!=NULL || DevicesAddresses.Magnetometer_I2CAddr!=0){
		Magnetometer = new Magnetometer(I2C_Interface, DevicesAddresses.Magnetometer_I2CAddr);
	}
	if (DevicesAddresses.Barometer_I2CAddr!=NULL || DevicesAddresses.Barometer_I2CAddr!=0){
		Barometer = new Barometer(I2C_Interface, DevicesAddresses.Barometer_I2CAddr);
	}
}

#endif //#ifndef SCP_HwCtrl__10_DOF__IMU_h
