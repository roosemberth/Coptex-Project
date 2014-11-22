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

#ifndef SCP_HwCtrl__10_DOF__Accelerometer_h
#define SCP_HwCtrl__10_DOF__Accelerometer_h

#include "../../SCP-Include/SCP-Config.h"
#include "../HwPlatforms/I2C-Bus.h"
#include <eigen3/Eigen/Dense>
#include "IMU.h"

// ************************************************************************
// 		Software API Definition for ADXL345 Digital Accelerometer
// ************************************************************************

#define ADXL345_ActInactCtrl_Act		1<<7
#define ADXL345_ActInactCtrl_ActX		1<<6
#define ADXL345_ActInactCtrl_ActY		1<<5
#define ADXL345_ActInactCtrl_ActZ		1<<4
#define ADXL345_ActInactCtrl_Inact		1<<3
#define ADXL345_ActInactCtrl_InactX		1<<2
#define ADXL345_ActInactCtrl_InactY		1<<1
#define ADXL345_ActInactCtrl_InactZ		1<<0

#define ADXL345_TapAxes_Suppress		1<<3
#define ADXL345_TapAxes_TapX			1<<2
#define ADXL345_TapAxes_TapY			1<<1
#define ADXL345_TapAxes_TapZ			1<<0

#define ADXL345_ActTapStatus_ActX		1<<6
#define ADXL345_ActTapStatus_ActY		1<<5
#define ADXL345_ActTapStatus_ActZ		1<<4
#define ADXL345_ActTapStatus_Asleep		1<<3
#define ADXL345_ActTapStatus_TapX		1<<2
#define ADXL345_ActTapStatus_TapY		1<<1
#define ADXL345_ActTapStatus_TapZ		1<<0

#define ADXL345_BWRate_LowPower			1<<4
#define ADXL345_BWRate_Rate 			0x0F	// 0b00001111
	#define ADXL345_BWRate_Rate_3200Hz			0x0F		// 0b00001111
	#define ADXL345_BWRate_Rate_1600Hz			0x0E		// 0b00001110
	#define ADXL345_BWRate_Rate_800Hz			0x0D		// 0b00001101
	#define ADXL345_BWRate_Rate_400Hz			0x0C		// 0b00001100
	#define ADXL345_BWRate_Rate_200Hz			0x0B		// 0b00001011
	#define ADXL345_BWRate_Rate_100Hz			0x0A		// 0b00001010
	#define ADXL345_BWRate_Rate_50Hz			0x09		// 0b00001001
	#define ADXL345_BWRate_Rate_25Hz			0x08		// 0b00001000
	#define ADXL345_BWRate_Rate_2_5Hz			0x07		// 0b00000111
	#define ADXL345_BWRate_Rate_6_25Hz			0x06		// 0b00000110
	#define ADXL345_BWRate_Rate_3_13Hz			0x05		// 0b00000101
	#define ADXL345_BWRate_Rate_1_56Hz			0x04		// 0b00000100
	#define ADXL345_BWRate_Rate_0_78Hz			0x03		// 0b00000011
	#define ADXL345_BWRate_Rate_0_39Hz			0x02		// 0b00000010
	#define ADXL345_BWRate_Rate_0_20Hz			0x01		// 0b00000001
	#define ADXL345_BWRate_Rate_0_10Hz			0x00		// 0b00000000

#define ADXL345_PowerCtrl_Link			1<<5
#define ADXL345_PowerCtrl_AutoSleep		1<<4
#define ADXL345_PowerCtrl_Measure		1<<3
#define ADXL345_PowerCtrl_Sleep			1<<2
#define ADXL345_PowerCtrl_Wakeup		0x03	// 0b00000011
	#define ADXL345_PowerCtrl_Wakeup_8Hz		0x00	// 0b00000000
	#define ADXL345_PowerCtrl_Wakeup_4Hz		0x01	// 0b00000001
	#define ADXL345_PowerCtrl_Wakeup_2Hz		0x02	// 0b00000010
	#define ADXL345_PowerCtrl_Wakeup_1Hz		0x03	// 0b00000011

#define ADXL345_IntEnable_DataReady		1<<7
#define ADXL345_IntEnable_SingleTap		1<<6
#define ADXL345_IntEnable_DoubleTap		1<<5
#define ADXL345_IntEnable_Activity		1<<4
#define ADXL345_IntEnable_Inactivity	1<<3
#define ADXL345_IntEnable_FreeFall		1<<2
#define ADXL345_IntEnable_Watermark		1<<1
#define ADXL345_IntEnable_Overrun		1<<0

#define ADXL345_IntMap_DataReady		1<<7
#define ADXL345_IntMap_SingleTap		1<<6
#define ADXL345_IntMap_DoubleTap		1<<5
#define ADXL345_IntMap_Activity			1<<4
#define ADXL345_IntMap_Inactivity		1<<3
#define ADXL345_IntMap_FreeFall			1<<2
#define ADXL345_IntMap_Watermark		1<<1
#define ADXL345_IntMap_Overrun			1<<0

	#define ADXL345_IntMap_Int1Pin				0x00
	#define ADXL345_IntMap_Int2Pin				0x01

#define ADXL345_IntSource_DataReady		1<<7
#define ADXL345_IntSource_SingleTap		1<<6
#define ADXL345_IntSource_DoubleTap		1<<5
#define ADXL345_IntSource_Activity		1<<4
#define ADXL345_IntSource_Inactivity	1<<3
#define ADXL345_IntSource_FreeFall		1<<2
#define ADXL345_IntSource_Watermark		1<<1
#define ADXL345_IntSource_Overrun		1<<0

#define ADXL345_DataFormat_SelfTest		1<<7
#define ADXL345_DataFormat_SPI			1<<6
#define ADXL345_DataFormat_IntInvert	1<<5
#define ADXL345_DataFormat_FullRes		1<<3
#define ADXL345_DataFormat_Justify		1<<2
#define ADXL345_DataFormat_Range		0x03	// 0b00000011
	#define ADXL345_DataFormat_Range_2G			0x00	// 0b00000000
	#define ADXL345_DataFormat_Range_4G			0x01	// 0b00000001
	#define ADXL345_DataFormat_Range_8G			0x02	// 0b00000010
	#define ADXL345_DataFormat_Range_16G		0x03	// 0b00000011

#define ADXL345_FifoCtrl_FifoMode		0xC0	// 0b11000000
	#define ADXL345_FifoCtrl_FifoMode_Bypass	0x00	// 0b00000000
	#define ADXL345_FifoCtrl_FifoMode_Fifo		0x40	// 0b01000000
	#define ADXL345_FifoCtrl_FifoMode_Stream	0x80	// 0b10000000
	#define ADXL345_FifoCtrl_FifoMode_Trigger	0xC0	// 0b11000000
#define ADXL345_FifoCtrl_Trigger		1<<5	// 0b00100000
#define ADXL345_FifoCtrl_Samples		0x1F	// 0b00011111

#define ADXL345_FifoStatus_FifoTrig		1<<7
#define ADXL345_FifoStatus_Entries		0x1F	// 0b00011111

using namespace HwCtrl;

class IMU::Accelerometer{
	public:
		class C_ADXL345{
			public:
				u8 DevID;
				u8 TapThreshhold;
				u8 XOffset;
				u8 YOffset;
				u8 ZOffset;
				u8 TapDuration;
				u8 TapLatency;
				u8 TapWindow;
				u8 ActivityThreshold;
				u8 InactivityThreshold;
				u8 InactivityTime;
				u8 ActInactCtrl;
				u8 FFThreshold;
				u8 FFTime;
				u8 TapAxes;
				u8 ActTapStatus;
				u8 BWRate;
				u8 PowerCtrl;
				u8 IntEnable;
				u8 IntMap;
				u8 IntSource;
				u8 DataFormat;
				u8 DataX0;
				u8 DataX1;
				u8 DataY0;
				u8 DataY1;
				u8 DataZ0;
				u8 DataZ1;
				u8 FifoCtrl;
				u8 FifoStatus;
				float Sensitivity;
				C_ADXL345(){
					DevID				= 0x00;
					TapThreshhold		= 0x1D;
					XOffset				= 0x1E;
					YOffset				= 0x1F;
					ZOffset				= 0x20;
					TapDuration			= 0x21;
					TapLatency			= 0x22;
					TapWindow			= 0x23;
					ActivityThreshold	= 0x24;
					InactivityThreshold	= 0x25;
					InactivityTime		= 0x26;
					ActInactCtrl		= 0x27;
					FFThreshold			= 0x28;
					FFTime				= 0x29;
					TapAxes				= 0x2A;
					ActTapStatus		= 0x2B;
					BWRate				= 0x2C;
					PowerCtrl			= 0x2D;
					IntEnable			= 0x2E;
					IntMap				= 0x2F;
					IntSource			= 0x30;
					DataFormat			= 0x31;
					DataX0				= 0x32;
					DataX1				= 0x33;
					DataY0				= 0x34;
					DataY1				= 0x35;
					DataZ0				= 0x36;
					DataZ1				= 0x37;
					FifoCtrl			= 0x38;
					FifoStatus			= 0x39;
					Sensitivity			= 0.0039;
				}
		} ADXL345;
		Accelerometer(I2C_Bus &I2C_Interface);
		bool UpdateData();
		LinAlg::Vector3d *AccelerationP();
		bool config(void *ConfigPacket);
	private:
		u8 GPB1;																// General-Purpose Buffer 1
		u8 GPB2;																// General-Purpose Buffer 2
		u8 AccelI2CAddress;
		I2C_Bus *IMU_Bus;
		LinAlg::Vector3d Acceleration;
};

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

#endif //#ifndef SCP_HwCtrl__10_DOF__Accelerometer_h
