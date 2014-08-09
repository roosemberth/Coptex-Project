/*
 * "SCP-Config File" - Coptex Project System Config
 *
 * Copyright (C) 2013-2015 Roosemberth Palacios <roosemberth@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2.
 *
 */

#include <boost/numeric/ublas/vector.hpp>

typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;

#define SCP_IMU_I2C_Bus "/dev/i2c-10"
#define SCP_Gyroscope_I2CAddr		0x69
#define SCP_Accelerometer_I2CAddr	0x53
#define SCP_Magnetometer_I2CAddr	0x1E
#define SCP_Barometer_I2CAddr		0x77

namespace LinAlg = boost::numeric::ublas;
