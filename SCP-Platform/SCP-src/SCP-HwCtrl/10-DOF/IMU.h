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

#include "../../SCP-Include/SCP-Config.h"
#include "../HwPlatforms/I2C-Bus.h"
#include "Gyroscope.h"
#include "Accelerometer.h"
#include "Magnetometer.h"
#include "Barometer.h"

#ifndef NULL
	#define NULL (void *)0
#endif

typedef unsigned char u8;

struct S_IMU_Addrs {
		u8 Gyroscope_I2CAddr;
		u8 Accelerometer_I2CAddr;
		u8 Magnetometer_I2CAddr;
		u8 Barometer_I2CAddr;
};

void IMU_Init(struct S_I2C_Bus_Data *I2C_Bus, struct S_IMU_Addrs DevicesAddresses){
	if (DevicesAddresses.Gyroscope_I2CAddr!=NULL || DevicesAddresses.Gyroscope_I2CAddr!=0){
		Gyroscope = Gyroscope(I2C_Bus, DevicesAddresses.Gyroscope_I2CAddr);
	}
	if (DevicesAddresses.Accelerometer_I2CAddr!=NULL|| DevicesAddresses.Accelerometer_I2CAddr!=0){
		Accelerometer = Accelerometer(I2C_Bus, DevicesAddresses.Accelerometer_I2CAddr);
	}
	if (DevicesAddresses.Magnetometer_I2CAddr!=NULL || DevicesAddresses.Magnetometer_I2CAddr!=0){
		Magnetometer = Magnetometer(I2C_Bus, DevicesAddresses.Magnetometer_I2CAddr);
	}
	if (DevicesAddresses.Barometer_I2CAddr!=NULL || DevicesAddresses.Barometer_I2CAddr!=0){
		Barometer = Barometer(I2C_Bus, DevicesAddresses.Barometer_I2CAddr);
	}
}

struct S_IMU {
		struct S_Gyroscope *Gyroscope;
		struct S_Accelerometer *Accelerometer;
		struct S_Magnetometer *Magnetometer;
		struct S_Barometer *Barometer;
		struct S_IMU_Addrs *IMU_Addrs;
		void (*Init)(struct I2C_Bus &I2C_Interface, struct IMU_Addrs Adresses);
};
IMU = {
		.Init = &IMU_Init
};

#endif //#ifndef SCP_HwCtrl__10_DOF__IMU_h
