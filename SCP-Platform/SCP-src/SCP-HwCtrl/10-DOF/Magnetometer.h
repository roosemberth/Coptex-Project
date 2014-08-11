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

#ifndef SCP_HwCtrl__10_DOF__Magnetometer_h
#define SCP_HwCtrl__10_DOF__Magnetometer_h

#include "../../SCP-Include/SCP-Config.h"
#include "../HwPlatforms/I2C-Bus.h"
#include <eigen3/Eigen/Dense>
#include "IMU.h"
#include <math.h>

// ************************************************************************
// 		Software API Definition for HMC5883L 3-Axis Digital Compass IC
// ************************************************************************
#define HMC5883L_ConfigRegA_CRA7				1<<7					// Future Use?
#define HMC5883L_ConfigRegA_AvgSamples			3<<5
	#define HMC5883L_ConfigRegA_AvgSamples_1			0<<5
	#define HMC5883L_ConfigRegA_AvgSamples_2			1<<5
	#define HMC5883L_ConfigRegA_AvgSamples_4			2<<5
	#define HMC5883L_ConfigRegA_AvgSamples_8			3<<5
#define HMC5883L_ConfigRegA_DataOutputRate		7<<5
	#define HMC5883L_ConfigRegA_DataOutputRate_0_75Hz	0<<2
	#define HMC5883L_ConfigRegA_DataOutputRate_1_5Hz	1<<2
	#define HMC5883L_ConfigRegA_DataOutputRate_3Hz		2<<2
	#define HMC5883L_ConfigRegA_DataOutputRate_7_5Hz	3<<2
	#define HMC5883L_ConfigRegA_DataOutputRate_15Hz		4<<2
	#define HMC5883L_ConfigRegA_DataOutputRate_30Hz		5<<2
	#define HMC5883L_ConfigRegA_DataOutputRate_75Hz		6<<2
	#define HMC5883L_ConfigRegA_DataOutputRate_Reserved	7<<2
#define HMC5883L_ConfigRegA_MeasureConfig		3<<0
	#define HMC5883L_ConfigRegA_MeasureConfig_Normal	0<<0
	#define HMC5883L_ConfigRegA_MeasureConfig_Positive	1<<0
	#define HMC5883L_ConfigRegA_MeasureConfig_Negative	2<<0
	#define HMC5883L_ConfigRegA_MeasureConfig_Reserved	3<<0

#define HMC5883L_ConfigRegB_GainConfig			7<<5
	#define HMC5883L_ConfigRegB_GainConfig_1370LSb_G	0<<5
	#define HMC5883L_ConfigRegB_GainConfig_1090LSb_G	1<<5
	#define HMC5883L_ConfigRegB_GainConfig_820LSb_G		2<<5
	#define HMC5883L_ConfigRegB_GainConfig_660LSb_G		3<<5
	#define HMC5883L_ConfigRegB_GainConfig_440LSb_G		4<<5
	#define HMC5883L_ConfigRegB_GainConfig_390LSb_G		5<<5
	#define HMC5883L_ConfigRegB_GainConfig_330LSb_G		6<<5
	#define HMC5883L_ConfigRegB_GainConfig_230LSb_G		7<<5
#define HMC5883L_ConfigRegB_ZeroBits			0x1F					// Should be Zero for Correct Operation

#define HMC5883L_ModeReg_HighSpeedI2C			1<<7
#define HMC5883L_ModeReg_ZeroBits				0x7C					// Should be Zero for Correct Operation
#define HMC5883L_ModeReg_ModeSelection			3<<0
	#define HMC5883L_ModeReg_ModeSelection_Continuous	0<<0
	#define HMC5883L_ModeReg_ModeSelection_Single		1<<0
	#define HMC5883L_ModeReg_ModeSelection_Idle			2<<0
	#define HMC5883L_ModeReg_ModeSelection_IdleMode		3<<0

#define HMC5883L_StatusReg_Zero					0xFC					// Should be Zero for Correct Operation
#define HMC5883L_StatusReg_Lock					1<<1
#define HMC5883L_StatusReg_Ready				1<<0

using namespace HwCtrl;

class IMU::Magnetometer{
public:
	class C_HMC5883L{
		u8 ConfigRegA;
		u8 ConfigRegB;
		u8 ModeReg;
		u8 DataOutXMSB;
		u8 DataOutXLSB;
		u8 DataOutYMSB;
		u8 DataOutYLSB;
		u8 DataOutZMSB;
		u8 DataOutZLSB;
		u8 StatusReg;
		u8 IDRegA;
		u8 IDRegB;
		u8 IDRegC;
		C_HMC5883L(){
			ConfigRegA		= 0x00;
			ConfigRegB		= 0x01;
			ModeReg			= 0x02;
			DataOutXMSB		= 0x03;
			DataOutXLSB		= 0x04;
			DataOutZMSB		= 0x05;
			DataOutZLSB		= 0x06;
			DataOutYMSB		= 0x07;
			DataOutYLSB		= 0x08;
			StatusReg		= 0x09;
			IDRegA			= 0x0A;
			IDRegB			= 0x0B;
			IDRegC			= 0x0C;
		}
	} HMC5883L;
	Magnetometer(I2C_Bus &I2C_Interface);
	bool UpdateData();
	LinAlg::Vector3d *AngularRateP();
	bool config(void *ConfigPacket);
private:
	u8 GPB1;																// General-Purpose Buffer 1
	u8 GPB2;																// General-Purpose Buffer 2
	u8 MagnetometerI2CAddress;
	I2C_Bus *IMU_Bus;
	LinAlg::Vector3d<double> MagneticField;
};

#endif // #ifndef SCP_HwCtrl__10_DOF__Magnetometer_h
