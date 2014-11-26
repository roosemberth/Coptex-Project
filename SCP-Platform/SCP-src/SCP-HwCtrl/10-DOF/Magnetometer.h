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

// ************************************************************************

struct S_HMC5883L_Magnetometer{
		const u8 ConfigRegA;
		const u8 ConfigRegB;
		const u8 ModeReg;
		const u8 DataOutXMSB;
		const u8 DataOutXLSB;
		const u8 DataOutYMSB;
		const u8 DataOutYLSB;
		const u8 DataOutZMSB;
		const u8 DataOutZLSB;
		const u8 StatusReg;
		const u8 IDRegA;
		const u8 IDRegB;
		const u8 IDRegC;
} HMC5883L_Magnetometer = {
		.ConfigRegA		= 0x00,
		.ConfigRegB		= 0x01,
		.ModeReg		= 0x02,
		.DataOutXMSB	= 0x03,
		.DataOutXLSB	= 0x04,
		.DataOutZMSB	= 0x05,
		.DataOutZLSB	= 0x06,
		.DataOutYMSB	= 0x07,
		.DataOutYLSB	= 0x08,
		.StatusReg		= 0x09,
		.IDRegA			= 0x0A,
		.IDRegB			= 0x0B,
		.IDRegC			= 0x0C
};

void Magnetometer_Init(struct S_I2C_Bus_Data *I2C_Bus, u8 Magnetometer_I2CAddr){
	Magnetometer.I2C_Address = Magnetometer_I2CAddr;
	Magnetometer.IMU_Bus = I2C_Bus;
	Magnetometer.MagneticField[0] = 0;
	Magnetometer.MagneticField[1] = 0;
	Magnetometer.MagneticField[2] = 0;
	char GPB1 = 0;
	char GPB2 = 0;
	if (Magnetometer.IMU_Bus->Read(Magnetometer.I2C_Address, Magnetometer.RegMap->IDRegA, &GPB1, 1)!=0x48)
		Magnetometer.SysStatus |= 1<<0;
	GPB1 = 0;
	if (Magnetometer.IMU_Bus->Read(Magnetometer.I2C_Address, Magnetometer.RegMap->IDRegB, &GPB1, 1)!=0x34)
		Magnetometer.SysStatus |= 1<<1;
	GPB1 = 0;
	if (Magnetometer.IMU_Bus->Read(Magnetometer.I2C_Address, Magnetometer.RegMap->IDRegC, &GPB1, 1)!=0x33)
		Magnetometer.SysStatus |= 1<<2;

	GPB1 = 0 | HMC5883L_ConfigRegA_AvgSamples_8 | \
			HMC5883L_ConfigRegA_DataOutputRate_15Hz | \
			HMC5883L_ConfigRegA_MeasureConfig_Normal;
	Magnetometer.IMU_Bus->Write(Magnetometer.I2C_Address, Magnetometer.RegMap->ConfigRegA, &GPB1, 1);
	GPB1 = 0 | HMC5883L_ConfigRegB_GainConfig_390LSb_G;
	Magnetometer.IMU_Bus->Write(Magnetometer.I2C_Address, Magnetometer.RegMap->ConfigRegB, &GPB1, 1);
	GPB1 = 0;
	Magnetometer.IMU_Bus->Write(Magnetometer.I2C_Address, Magnetometer.RegMap->ModeReg, &GPB1, 1);

	UpdateData();
}

char Magnetometer_UpdateData(){
	char ret;
	char GPB1 = 0;
	char GPB2 = 0;
	Magnetometer.MagneticField[0] = 0;
	Magnetometer.MagneticField[1] = 0;
	Magnetometer.MagneticField[2] = 0;

	//TODO:[Critical] Implement Error-Notifying Mechanism
	if (Magnetometer.IMU_Bus->Read(Magnetometer.I2C_Address, Magnetometer.RegMap->DataOutXMSB, &GPB1, 1)) ret |= 1<<0;
	if (Magnetometer.IMU_Bus->Read(Magnetometer.I2C_Address, Magnetometer.RegMap->DataOutXLSB, &GPB2, 1)) ret |= 1<<1;
	MagneticField(0) = ((u16) ((GPB1<<8) | GPB2)) /* TODO:[Critical] Multiply by Scaling Constant */;

	//TODO:[Critical] Implement Error-Notifying Mechanism
	if (Magnetometer.IMU_Bus->Read(Magnetometer.I2C_Address, Magnetometer.RegMap->DataOutYMSB, &GPB1, 1)) ret |= 1<<2;
	if (Magnetometer.IMU_Bus->Read(Magnetometer.I2C_Address, Magnetometer.RegMap->DataOutYLSB, &GPB2, 1)) ret |= 1<<3;
	MagneticField(1) = ((u16) ((GPB1<<8) | GPB2)) /* TODO:[Critical] Multiply by Scaling Constant */;
	//TODO:[Critical] Implement Error-Notifying Mechanism
	if (Magnetometer.IMU_Bus->Read(Magnetometer.I2C_Address, Magnetometer.RegMap->DataOutZMSB, &GPB1, 1)) ret |= 1<<4;
	if (Magnetometer.IMU_Bus->Read(Magnetometer.I2C_Address, Magnetometer.RegMap->DataOutZLSB, &GPB2, 1)) ret |= 1<<5;
	MagneticField(2) = ((u16) ((GPB1<<8) | GPB2)) /* TODO:[Critical] Multiply by Scaling Constant */;
	return ret;
}

void Magnetometer_Update_SysStatus(){
	//TODO:[Optional] Implement Config Manager
}

int Magnetometer_Config(){
	int ret = 0;
	//TODO:[Optional] Implement Config Manager
	return ret;
}

struct S_Magnetometer{
		struct S_HMC5883L_Magnetometer *RegMap;
		struct S_I2C_Bus_Data *IMU_Bus;
		u8 I2C_Address;
		long MagneticField;
		char SysStatus;
		void (*Init)		(struct S_I2C_Bus_Data *I2C_Bus, u8 Magnetometer_I2CAddr);
		char (*UpdateData)	(void);
		void (*UpdateSysStatus)	(void);
		int  (*Config)		(void *ConfigPacket);
} Magnetometer = {
		.RegMap = &HMC5883L_Magnetometer,
		.Init	= &Magnetometer_Init,
		.UpdateData 	= &Magnetometer_UpdateData,
		.UpdateSysStatus= &Magnetometer_Update_SysStatus,
		.Config			= &Magnetometer_Config
};

#endif // #ifndef SCP_HwCtrl__10_DOF__Magnetometer_h
