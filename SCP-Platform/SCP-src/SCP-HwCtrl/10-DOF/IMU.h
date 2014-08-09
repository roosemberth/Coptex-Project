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

#include "Gyroscope.h"
#include "Accelerometer.h"
#include "Magnetometer.h"
#include "Barometer.h"

using namespace HwCtrl;

class IMU{
	public:
		class Gyroscope;
		class Accelerometer;
		class Magnetometer;
		class Barometer;
	private:

};

#endif //#ifndef SCP_HwCtrl__10_DOF__IMU_h
