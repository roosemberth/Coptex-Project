/*
 * "ADXL345 3-Axis Digital Accelerometer" - Coptex Project Hardware Control
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
 * The ADXL345 is a small, thin, ultralow power, 3-axis accelerometer with
 * high resolution (13-bit) measurement at up to ±16 g. Digital output data
 * is formatted as 16-bit twos complement and is accessible through either
 * a SPI (3- or 4-wire) or I2C digital interface.
 */

#include "../../SCP-Include/SCP-Config.h"
#include "../HwPlatforms/I2C-Bus.h"
#include <eigen3/Eigen/Dense>
#include "Accelerometer.h"

using namespace HwCtrl;

bool IMU::Accelerometer::UpdateData(){
	GPB1 = 0;
	GPB2 = 0;
	Acceleration << 0, 0, 0;
	if (IMU_Bus->Read(AccelI2CAddress, ADXL345.DataX1, &GPB1, 1)) return true;
	if (IMU_Bus->Read(AccelI2CAddress, ADXL345.DataX0, &GPB2, 1)) return true;
	Acceleration(0) = ((u16) ((GPB1<<8) | GPB2)) * ADXL345.Sensitivity * SCP_Current_Gravity;
	if (IMU_Bus->Read(AccelI2CAddress, ADXL345.DataY1, &GPB1, 1)) return true;
	if (IMU_Bus->Read(AccelI2CAddress, ADXL345.DataY0, &GPB2, 1)) return true;
	Acceleration(1) = ((u16) ((GPB1<<8) | GPB2)) * ADXL345.Sensitivity * SCP_Current_Gravity;
	if (IMU_Bus->Read(AccelI2CAddress, ADXL345.DataZ1, &GPB1, 1)) return true;
	if (IMU_Bus->Read(AccelI2CAddress, ADXL345.DataZ0, &GPB2, 1)) return true;
	Acceleration(2) = ((u16) ((GPB1<<8) | GPB2)) * ADXL345.Sensitivity * SCP_Current_Gravity;
	return false;
}

IMU::Accelerometer::Accelerometer(I2C_Bus &I2C_Interface){
	AccelI2CAddress = SCP_Gyroscope_I2CAddr;
	IMU_Bus = I2C_Interface;
	Acceleration << 0, 0, 0;
	GPB1 = 0;
	GPB2 = 0;
//	if (IMU_Bus->Read(AccelI2CAddress, ADXL345.DevID, &GPB1, 1)!=0xE5) //TODO:[Critical] Implement Error-Notifying Mechanism
	GPB1 = 0 | ADXL345_PowerCtrl_Measure;
	IMU_Bus->Write(AccelI2CAddress, ADXL345.PowerCtrl, &GPB1, 1);

	GPB1 = 0;
	IMU_Bus->Read(AccelI2CAddress, ADXL345.DataFormat, &GPB1, 1);
	// Preserve the following values untouched
	GPB1 &= (ADXL345_DataFormat_SelfTest | ADXL345_DataFormat_SPI | ADXL345_DataFormat_IntInvert | ADXL345_DataFormat_FullRes);
	// Set the Range to +/- 2G and FullResolution
	GPB1 |=  ADXL345_DataFormat_Range_2G | ADXL345_DataFormat_FullRes;
	IMU_Bus->Write(AccelI2CAddress, ADXL345.DataFormat, &GPB1, 1);

	GPB1 = 0 | ADXL345_BWRate_Rate_100Hz;
	IMU_Bus->Write(AccelI2CAddress, ADXL345.BWRate, &GPB1, 1);

	GPB1 = 0;
	IMU_Bus->Write(AccelI2CAddress, ADXL345.TapThreshhold, &GPB1, 1);
	IMU_Bus->Write(AccelI2CAddress, ADXL345.TapDuration, &GPB1, 1);
	IMU_Bus->Write(AccelI2CAddress, ADXL345.TapLatency, &GPB1, 1);
	IMU_Bus->Write(AccelI2CAddress, ADXL345.TapWindow, &GPB1, 1);
	IMU_Bus->Write(AccelI2CAddress, ADXL345.ActivityThreshold, &GPB1, 1);
	IMU_Bus->Write(AccelI2CAddress, ADXL345.InactivityThreshold, &GPB1, 1);
	IMU_Bus->Write(AccelI2CAddress, ADXL345.InactivityTime, &GPB1, 1);
	IMU_Bus->Write(AccelI2CAddress, ADXL345.FFThreshold, &GPB1, 1);
	IMU_Bus->Write(AccelI2CAddress, ADXL345.FFTime, &GPB1, 1);

	GPB1 = 0;
	IMU_Bus->Read(AccelI2CAddress, ADXL345.ActInactCtrl, &GPB1, 1);
	// Preserve the following values untouched
	GPB1 &= (ADXL345_ActInactCtrl_Act | ADXL345_ActInactCtrl_Inact);
	// Disable any axis participation on detecting Activity or Inactivity
	GPB1 |=  0;
	IMU_Bus->Write(AccelI2CAddress, ADXL345.ActInactCtrl, &GPB1, 1);

	GPB1 = 0;
	IMU_Bus->Read(AccelI2CAddress, ADXL345.TapAxes, &GPB1, 1);
	// Preserve the following values untouched, 0x0F<<4 Corresponds to not well-defined bits on Datasheet
	GPB1 &= (0x0F<<4 | ADXL345_TapAxes_Suppress);
	// Disable All Axis Participation on Tap Detection
	GPB1 |=  0;
	IMU_Bus->Write(AccelI2CAddress, ADXL345.TapAxes, &GPB1, 1);

	UpdateData();
}

LinAlg::Vector3d *IMU::Accelerometer::AccelerationP(){
	return &Acceleration;
}

bool IMU::Accelerometer::config(void *ConfigPacket){
	//TODO:[Optional] Implement Config Manager
	// Set and Get of Range and DataRate suggested
	return false;
}
