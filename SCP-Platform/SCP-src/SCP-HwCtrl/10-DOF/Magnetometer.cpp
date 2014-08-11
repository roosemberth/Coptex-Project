/*
 * "HMC5883L 3-Axis Digital Compass IC" - Coptex Project Hardware Control
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
 * The Honeywell HMC5883L is a surface-mount, multi-chip module designed
 * for low-field magnetic sensing with a digital interface for applications
 * such as low-cost compassing and magnetometry. The HMC5883L includes our
 * state-of-the-art, high-resolution HMC118X series magneto-resistive sensors
 * plus an ASIC containing amplification, automatic degaussing strap drivers,
 * offset cancellation, and a 12-bit ADC that enables 1° to 2° compass heading
 * accuracy.
 */

#include "../../SCP-Include/SCP-Config.h"
#include "../HwPlatforms/I2C-Bus.h"
#include <eigen3/Eigen/Dense>
#include "Magnetometer.h"

using namespace HwCtrl;

bool IMU::Magnetometer::UpdateData(){
	GPB1 = 0;
	GPB2 = 0;
	MagneticField << 0, 0, 0;

	if (IMU_Bus->Read(MagnetometerI2CAddress, HMC5883L.DataOutXMSB, &GPB1, 1)) return true;
	if (IMU_Bus->Read(MagnetometerI2CAddress, HMC5883L.DataOutXLSB, &GPB2, 1)) return true;
	MagneticField(0) = ((u16) ((GPB1<<8) | GPB2)) /* TODO:[Critical] Multiply by Scaling Constant */;
	if (IMU_Bus->Read(MagnetometerI2CAddress, HMC5883L.DataOutYMSB, &GPB1, 1)) return true;
	if (IMU_Bus->Read(MagnetometerI2CAddress, HMC5883L.DataOutYLSB, &GPB2, 1)) return true;
	MagneticField(1) = ((u16) ((GPB1<<8) | GPB2)) /* TODO:[Critical] Multiply by Scaling Constant */;
	if (IMU_Bus->Read(MagnetometerI2CAddress, HMC5883L.DataOutZMSB, &GPB1, 1)) return true;
	if (IMU_Bus->Read(MagnetometerI2CAddress, HMC5883L.DataOutZLSB, &GPB2, 1)) return true;
	MagneticField(2) = ((u16) ((GPB1<<8) | GPB2)) /* TODO:[Critical] Multiply by Scaling Constant */;

	return false;

}

IMU::Magnetometer::Magnetometer(I2C_Bus &I2C_Interface){
	MagnetometerI2CAddress = SCP_Magnetometer_I2CAddr;
	IMU_Bus = I2C_Interface;
	MagneticField << 0, 0, 0;
	GPB1 = 0;
	GPB2 = 0;
	//if (IMU_Bus->Read(MagnetometerI2CAddress, HMC5883L.IDRegA, &GPB1, 1)!=0x48) return true; //TODO:[Critical] Implement Error-Notifying Mechanism
	GPB1 = 0;
	//if (IMU_Bus->Read(MagnetometerI2CAddress, HMC5883L.IDRegB, &GPB1, 1)!=0x34) return true; //TODO:[Critical] Implement Error-Notifying Mechanism
	GPB1 = 0;
	//if (IMU_Bus->Read(MagnetometerI2CAddress, HMC5883L.IDRegC, &GPB1, 1)!=0x33) return true; //TODO:[Critical] Implement Error-Notifying Mechanism

	GPB1 = 0 | HMC5883L_ConfigRegA_AvgSamples_8 | HMC5883L_ConfigRegA_DataOutputRate_15Hz | HMC5883L_ConfigRegA_MeasureConfig_Normal;
	IMU_Bus->Write(MagnetometerI2CAddress, HMC5883L.ConfigRegA, &GPB1, 1);
	GPB1 = 0 | HMC5883L_ConfigRegB_GainConfig_390LSb_G;
	IMU_Bus->Write(MagnetometerI2CAddress, HMC5883L.ConfigRegB, &GPB1, 1);
	GPB1 = 0;
	IMU_Bus->Write(MagnetometerI2CAddress, HMC5883L.ModeReg, &GPB1, 1);

	UpdateData();
}
