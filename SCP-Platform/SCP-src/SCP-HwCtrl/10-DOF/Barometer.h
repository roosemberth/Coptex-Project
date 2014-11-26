/*
 * "BMP085 Digital pressure sensor" - Coptex Project Hardware Control
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
 * The BMP085 is a new generation of high precision digital pressure sensors
 * for consumer applications. The BMP085 is based on piezo-resistive technology
 * for EMC robustness, high accuracy and linearity as well as long term stability.
 * The ultra-low power, low voltage electronics of the BMP085 is optimized for
 * use in mobile phones, PDAs, GPS navigation devices and outdoor equipment. With
 * a low altitude noise of merely 0.25m at fast conversion time, the BMP085 offers
 * superior performance. The I2C interface allows for easy system integration with
 * a microcontroller.
 */

#ifndef SCP_HwCtrl__10DOF__Barometer_h
#define SCP_HwCtrl__10DOF__Barometer_h

#include "../../SCP-Include/SCP-Config.h"
#include "../HwPlatforms/I2C-Bus.h"

typedef unsigned char u8;

struct S_BMP085_Barometer{
		const u8 AC1H;
		const u8 AC1L;
		const u8 AC2H;
		const u8 AC2L;
		const u8 AC3H;
		const u8 AC3L;
		const u8 AC4H;
		const u8 AC4L;
		const u8 AC5H;
		const u8 AC5L;
		const u8 AC6H;
		const u8 AC6L;
		const u8 B1H;
		const u8 B1L;
		const u8 B2H;
		const u8 B2L;
		const u8 MBH;
		const u8 MBL;
		const u8 MCH;
		const u8 MCL;
		const u8 MDH;
		const u8 MDL;
} BMP085_Barometer = {
		.AC1H = 0xAA,
		.AC1L = 0xAB,
		.AC2H = 0xAC,
		.AC2L = 0xAD,
		.AC3H = 0xAE,
		.AC3L = 0xAF,
		.AC4H = 0xB0,
		.AC4L = 0xB1,
		.AC5H = 0xB2,
		.AC5L = 0xB3,
		.AC6H = 0xB4,
		.AC6L = 0xB5,
		.B1H = 0xB6,
		.B1L = 0xB7,
		.B2H = 0xB8,
		.B2L = 0xB9,
		.MBH = 0xBA,
		.MBL = 0xBB,
		.MCH = 0xBC,
		.MCL = 0xBD,
		.MDH = 0xBE,
		.MDL = 0xBF
};

void Barometer_Init(struct S_I2C_Bus_Data *I2C_Bus, u8 Barometer_I2CAddr){
	struct S_BMP085_Barometer_CalibrationValues DefaultCalibrationValues;
	char GPB1 = 0;
	char GPB2 = 0;
	Barometer.CalibrationValues = &DefaultCalibrationValues;
	Barometer.I2C_Address= Barometer_I2CAddr;
	Barometer.IMU_Bus = I2C_Bus;
	Barometer.Preassure = 0;
	Barometer.Temperature = 0;
	Barometer.SysStatus = 0;
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->AC1H, &GPB1, 1))
		Barometer.SysStatus |= 1<<0;
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->AC1L, &GPB2, 1))
		Barometer.SysStatus |= 1<<0;
	Barometer.CalibrationValues->AC1 = ((int) ((GPB1<<8) | GPB2));
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->AC2H, &GPB1, 1))
		Barometer.SysStatus |= 1<<1;
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->AC2L, &GPB2, 1))
		Barometer.SysStatus |= 1<<1;
	Barometer.CalibrationValues->AC2 = ((int) ((GPB1<<8) | GPB2));
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->AC3H, &GPB1, 1))
		Barometer.SysStatus |= 1<<2;
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->AC3L, &GPB2, 1))
		Barometer.SysStatus |= 1<<2;
	Barometer.CalibrationValues->AC3 = ((int) ((GPB1<<8) | GPB2));
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->AC4H, &GPB1, 1))
		Barometer.SysStatus |= 1<<3;
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->AC4L, &GPB2, 1))
		Barometer.SysStatus |= 1<<3;
	Barometer.CalibrationValues->AC4 = ((int) ((GPB1<<8) | GPB2));
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->AC5H, &GPB1, 1))
		Barometer.SysStatus |= 1<<4;
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->AC5L, &GPB2, 1))
		Barometer.SysStatus |= 1<<4;
	Barometer.CalibrationValues->AC5 = ((int) ((GPB1<<8) | GPB2));
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->AC6H, &GPB1, 1))
		Barometer.SysStatus |= 1<<5;
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->AC6L, &GPB2, 1))
		Barometer.SysStatus |= 1<<5;
	Barometer.CalibrationValues->AC6 = ((int) ((GPB1<<8) | GPB2));
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->B1H, &GPB1, 1))
		Barometer.SysStatus |= 1<<6;
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->B1L, &GPB2, 1))
		Barometer.SysStatus |= 1<<6;
	Barometer.CalibrationValues->B1 = ((int) ((GPB1<<8) | GPB2));
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->B2H, &GPB1, 1))
		Barometer.SysStatus |= 1<<6;
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->B2L, &GPB2, 1))
		Barometer.SysStatus |= 1<<6;
	Barometer.CalibrationValues->B2 = ((int) ((GPB2<<8) | GPB2));
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->MBH, &GPB1, 1))
		Barometer.SysStatus |= 1<<7;
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->MBL, &GPB2, 1))
		Barometer.SysStatus |= 1<<7;
	Barometer.CalibrationValues->MB = ((int) ((GPB1<<8) | GPB2));
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->MCH, &GPB1, 1))
		Barometer.SysStatus |= 1<<7;
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->MCL, &GPB2, 1))
		Barometer.SysStatus |= 1<<7;
	Barometer.CalibrationValues->MC = ((int) ((GPB1<<8) | GPB2));
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->MDH, &GPB1, 1))
		Barometer.SysStatus |= 1<<7;
	if (Barometer.IMU_Bus->Read(Barometer.I2C_Address, Barometer.RegMap->MDL, &GPB2, 1))
		Barometer.SysStatus |= 1<<7;
	Barometer.CalibrationValues->MD = ((int) ((GPB1<<8) | GPB2));

	Barometer.UpdateData();
}

char Barometer_UpdateData(){
	char ret = 0;
	// TODO:[Critical] Implementation Pending!
	// ret |= 1<<0;
	return 0;
}

void Barometer_Update_SysStatus(){

}

int Barometer_Config(){
	int ret = 0;
	//TODO:[Optional] Implement Config Manager
	return ret;
}

struct S_BMP085_Barometer_CalibrationValues{
		int AC1;
		int AC2;
		int AC3;
		unsigned int AC4;
		unsigned int AC5;
		unsigned int AC6;
		int B1;
		int B2;
		int MB;
		int MC;
		int MD;
		long B5;
};

struct S_Barometer{
		struct S_BMP085_Barometer *RegMap;
		struct S_I2C_Bus_Data *IMU_Bus;
		u8 I2C_Address;
		long Preassure;
		char Temperature;
		char SysStatus;
		void (*Init)		(struct S_I2C_Bus_Data *I2C_Bus, u8 Barometer_I2CAddr);
		char (*UpdateData)	(void);
		void (*UpdateSysStatus)	(void);
		int  (*Config)		(void *ConfigPacket);
		struct S_BMP085_Barometer_CalibrationValues *CalibrationValues;
} Barometer = {
		.RegMap = &BMP085_Barometer,
		.Init	= &Barometer_Init,
		.UpdateData		= &Barometer_UpdateData,
		.UpdateSysStatus= &Barometer_Update_SysStatus,
		.Config			= &Barometer_Config,
		.SysStatus		= 0
};

#endif	// #ifndef SCP_HwCtrl__10DOF__Barometer_h
