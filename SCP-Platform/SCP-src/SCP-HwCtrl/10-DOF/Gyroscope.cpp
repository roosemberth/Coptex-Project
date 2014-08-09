/*
 * "L3G4200D 3-Axis Angular Rate Sensor" - Coptex Project Hardware Control
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
 * The L3G4200D is a low-power three-axis angular rate sensor able
 * to provide unprecedented stablility of zero rate level and sensitivity
 * over temperature and time. It includes a sensing element and an IC
 * interface capable of providing the measured angular rate to the external
 * world through a digital interface (I2C/SPI).
 */

#include <boost/numeric/ublas/vector.hpp>
#include "../../SCP-Include/SCP-Config.h"
#include "../HwPlatforms/I2C-Bus.h"
#include "IMU.h"
#include "Gyroscope.h"


IMU::Gyroscope::Gyroscope(I2C_Bus &I2C_Interface){
	GyroI2CAddress = SCP_Gyroscope_I2CAddr;
	IMU_Bus = I2C_Interface;
	//TODO: Implement System Initialization
	Status = 0;
	Temperature = 0;
	AngularRate(1) = 1;
	AngularRate(2) = 2;
	AngularRate(3) = 2;
}
