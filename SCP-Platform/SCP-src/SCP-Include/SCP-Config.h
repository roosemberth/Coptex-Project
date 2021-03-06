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

typedef unsigned char 	u8;
typedef unsigned short 	u16;
typedef unsigned int 	u32;

#define SCP_Gyroscope_I2CAddr		0x69
#define SCP_Accelerometer_I2CAddr	0x53
#define SCP_Magnetometer_I2CAddr	0x1E
#define SCP_Barometer_I2CAddr		0x77

#define SCP_MeanSV_Gravity 9.81431389123696816004;
#define SCP_MeanCH_Gravity 9.79533848562478986507;

#define STORE_FLOAT_ON_INT(a)


/*
double SCP_Current_Gravity = SCP_MeanSV_Gravity; //9.80665;

double CalculateGravity(double Latitude, double MSL){
	return 9.780327*(1 + (0.0053024*pow(sin(Latitude), 2)) - 0.0000058*pow(sin(2*Latitude),2)) - 3.086*pow(10, -6)*MSL;
	// According to: http://www.npl.co.uk/reference/faqs/how-can-i-determine-my-local-values-of-gravitational-acceleration-and-altitude-(faq-pressure)
}
*/

