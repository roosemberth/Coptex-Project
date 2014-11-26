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

#ifndef SCP_HwCtrl__10_DOF__Gyroscope_h
#define SCP_HwCtrl__10_DOF__Gyroscope_h

#include "../../SCP-Include/SCP-Config.h"
#include "../HwPlatforms/I2C-Bus.h"

// ************************************************************************
// 		Software API Definition for L3G4200D MEMS Angular Rate Sensor
// ************************************************************************
#define L3G4200D_CtrlReg1_DR1 		1<<7
#define L3G4200D_CtrlReg1_DR0 		1<<6
#define L3G4200D_CtrlReg1_BW1 		1<<5
#define L3G4200D_CtrlReg1_BW0 		1<<4
#define L3G4200D_CtrlReg1_PD 		1<<3
#define L3G4200D_CtrlReg1_Zen 		1<<2
#define L3G4200D_CtrlReg1_Yen 		1<<1
#define L3G4200D_CtrlReg1_Xen		1<<0

#define L3G4200D_CtrlReg2_HPM1 		1<<5
#define L3G4200D_CtrlReg2_HPM0 		1<<4
#define L3G4200D_CtrlReg2_HPCF3 	1<<3
#define L3G4200D_CtrlReg2_HPCF2 	1<<2
#define L3G4200D_CtrlReg2_HPCF1 	1<<1
#define L3G4200D_CtrlReg2_HPCF0 	1<<0

#define L3G4200D_CtrlReg3_I1Int 	1<<7
#define L3G4200D_CtrlReg3_I1Boot	1<<6
#define L3G4200D_CtrlReg3_HLActive	1<<5
#define L3G4200D_CtrlReg3_PPOD		1<<4
#define L3G4200D_CtrlReg3_I2DRDY	1<<3
#define L3G4200D_CtrlReg3_I2WTM		1<<2
#define L3G4200D_CtrlReg3_I2ORun	1<<1
#define L3G4200D_CtrlReg3_I2Empty	1<<0

#define L3G4200D_CtrlReg4_BDU		1<<7
#define L3G4200D_CtrlReg4_BLE		1<<6
#define L3G4200D_CtrlReg4_FS1		1<<5
#define L3G4200D_CtrlReg4_FS0		1<<4
	#define L3G4200D_Sensitivity_S_250dps 	0
	#define L3G4200D_Sensitivity_S_500dps 	1<<4
	#define L3G4200D_Sensitivity_S_2000dps	1<<5
#define L3G4200D_CtrlReg4_ST1		1<<2
#define L3G4200D_CtrlReg4_ST0		1<<1
#define L3G4200D_CtrlReg4_SIM		1<<0

#define L3G4200D_CtrlReg5_Boot		1<<7
#define L3G4200D_CtrlReg5_FifoEn	1<<6
#define L3G4200D_CtrlReg5_HPen		1<<4
#define L3G4200D_CtrlReg5_INT1Sel1	1<<3
#define L3G4200D_CtrlReg5_INT1Sel0	1<<2
#define L3G4200D_CtrlReg5_OutSel1	1<<1
#define L3G4200D_CtrlReg5_OutSel0	1<<0

#define L3G4200D_Status_ZYXOR		1<<7
#define L3G4200D_Status_ZOR 		1<<6
#define L3G4200D_Status_YOR 		1<<5
#define L3G4200D_Status_XOR 		1<<4
#define L3G4200D_Status_ZYXDA		1<<3
#define L3G4200D_Status_ZDA 		1<<2
#define L3G4200D_Status_YDA 		1<<1
#define L3G4200D_Status_XDA 		1<<0

#define L3G4200D_FifoCtrl_FM2		1<<7
#define L3G4200D_FifoCtrl_FM1		1<<6
#define L3G4200D_FifoCtrl_FM0		1<<5
#define L3G4200D_FifoCtrl_Wtm4		1<<4
#define L3G4200D_FifoCtrl_Wtm3		1<<3
#define L3G4200D_FifoCtrl_Wtm2		1<<2
#define L3G4200D_FifoCtrl_Wtm1		1<<1
#define L3G4200D_FifoCtrl_Wtm0		1<<0

#define L3G4200D_FifoSrc_Wtm		1<<7
#define L3G4200D_FifoSrc_Ovrn		1<<6
#define L3G4200D_FifoSrc_Empty		1<<5
#define L3G4200D_FifoSrc_FSS4		1<<4
#define L3G4200D_FifoSrc_FSS3		1<<3
#define L3G4200D_FifoSrc_FSS2		1<<2
#define L3G4200D_FifoSrc_FSS1		1<<1
#define L3G4200D_FifoSrc_FSS0		1<<0

#define L3G4200D_INT1Cfg_AndOr		1<<7
#define L3G4200D_INT1Cfg_LIR		1<<6
#define L3G4200D_INT1Cfg_ZHIE		1<<5
#define L3G4200D_INT1Cfg_ZLIE		1<<4
#define L3G4200D_INT1Cfg_YHIE		1<<3
#define L3G4200D_INT1Cfg_YLIE		1<<2
#define L3G4200D_INT1Cfg_XHIE		1<<1
#define L3G4200D_INT1Cfg_XLIE		1<<0

#define L3G4200D_INT1Src_IA			1<<6
#define L3G4200D_INT1Src_ZH 		1<<5
#define L3G4200D_INT1Src_ZL 		1<<4
#define L3G4200D_INT1Src_YH 		1<<3
#define L3G4200D_INT1Src_YL 		1<<2
#define L3G4200D_INT1Src_XH 		1<<1
#define L3G4200D_INT1Src_XL 		1<<0

#define L3G4200D_INT1Duration_Wait	1<<7
#define L3G4200D_INT1Duration_D6	1<<6
#define L3G4200D_INT1Duration_D5	1<<5
#define L3G4200D_INT1Duration_D4	1<<4
#define L3G4200D_INT1Duration_D3	1<<3
#define L3G4200D_INT1Duration_D2	1<<2
#define L3G4200D_INT1Duration_D1	1<<1
#define L3G4200D_INT1Duration_D0	1<<0

// ************************************************************************

typedef unsigned char u8;

struct S_L3G4200D_Gyroscope{
		const u8 Who_Am_I;
		const u8 CtrlReg1;
		const u8 CtrlReg2;
		const u8 CtrlReg3;
		const u8 CtrlReg4;
		const u8 CtrlReg5;
		const u8 Reference;
		const u8 OutTemp;
		const u8 StatusReg;
		const u8 OutXL;
		const u8 OutXH;
		const u8 OutYL;
		const u8 OutYH;
		const u8 OutZL;
		const u8 OutZH;
		const u8 FifoCtrlReg;
		const u8 FifoSrcReg;
		const u8 Int1Cfg;
		const u8 Int1Src;
		const u8 Int1TshXH;
		const u8 Int1TshXL;
		const u8 Int1TshYH;
		const u8 Int1TshYL;
		const u8 Int1TshZH;
		const u8 Int1TshZL;
		const u8 Int1Duration;
		struct S_Sensitivity{
				// TODO: [Critical] Fix 'double' type use
				const long S_250dps;
				const long S_500dps;
				const long S_2000dps;
				long Current;
		} Sensitivity;
} L3G4200D_Gyroscope = {
		.Who_Am_I = 0x0F,
		.CtrlReg1 = 0x20,
		.CtrlReg2 = 0x21,
		.CtrlReg3 = 0x22,
		.CtrlReg4 = 0x23,
		.CtrlReg5 = 0x24,
		.Reference = 0x25,
		.OutTemp = 0x26,
		.StatusReg = 0x27,
		.OutXL = 0x28,
		.OutXH = 0x29,
		.OutYL = 0x2A,
		.OutYH = 0x2B,
		.OutZL = 0x2C,
		.OutZH = 0x2D,
		.FifoCtrlReg = 0x2E,
		.FifoSrcReg = 0x2F,
		.Int1Cfg = 0x30,
		.Int1Src = 0x31,
		.Int1TshXH = 0x32,
		.Int1TshXL = 0x33,
		.Int1TshYH = 0x34,
		.Int1TshYL = 0x35,
		.Int1TshZH = 0x36,
		.Int1TshZL = 0x37,
		.Int1Duration = 0x38,
		.Sensitivity = {
				// TODO [Relevant] Fix PI
				.S_250dps = 0.00875 * 3.141592,
				.S_500dps = 0.0175 * 3.141592,
				.S_2000dps = 0.07 * 3.141592,
				.Current = 0
		}
};

void Gyroscope_Init(struct S_I2C_Bus_Data *I2C_Bus, u8 Gyroscope_I2CAddr){
	char GPB1 = 0;
	char GPB2 = 0;
	Gyroscope.I2C_Address = Gyroscope_I2CAddr;
	Gyroscope.IMU_Bus = I2C_Bus;
	Gyroscope.AngularRate[0] = 0;
	Gyroscope.AngularRate[1] = 0;
	Gyroscope.AngularRate[2] = 0;
	Gyroscope.TemperatureDelta = 0;
	Gyroscope.SysStatus = 0;
	// TODO:[Critical] Implement Error-Notifying Mechanism
	if (Gyroscope.IMU_Bus->Read(Gyroscope.I2C_Address, Gyroscope.RegMap->Who_Am_I, &GPB1, 1)!=0xD3)
		Gyroscope.SysStatus |= 1<<0;
	GPB1 = 0 | L3G4200D_CtrlReg1_PD | \
			L3G4200D_CtrlReg1_Xen | \
			L3G4200D_CtrlReg1_Yen | \
			L3G4200D_CtrlReg1_Zen;
	Gyroscope.IMU_Bus->Write(Gyroscope.I2C_Address, Gyroscope.RegMap->CtrlReg1, &GPB1, 1);
	GPB1 = 0;
	Gyroscope.IMU_Bus->Write(Gyroscope.I2C_Address, Gyroscope.RegMap->CtrlReg2, &GPB1, 1);
	GPB1 = 0 | L3G4200D_CtrlReg3_I2DRDY;
	Gyroscope.IMU_Bus->Write(Gyroscope.I2C_Address, Gyroscope.RegMap->CtrlReg3, &GPB1, 1);
	GPB1 = 0 | L3G4200D_Sensitivity_S_250dps;
	Gyroscope.RegMap->Sensitivity.Current = Gyroscope.RegMap->Sensitivity.S_250dps;
	Gyroscope.IMU_Bus->Write(Gyroscope.I2C_Address, Gyroscope.RegMap->CtrlReg4, &GPB1, 1);
	GPB1 = 0;
	Gyroscope.IMU_Bus->Write(Gyroscope.I2C_Address, Gyroscope.RegMap->CtrlReg5, &GPB1, 1);

	Gyroscope.UpdateData();
}

char Gyroscope_UpdateData(){
	char ret = 0;
	char GPB1 = 0;
	char GPB2 = 0;
	Gyroscope.AngularRate = {0,0,0}
	if (Gyroscope.IMU_Bus->Read(Gyroscope.I2C_Address, Gyroscope.RegMap->OutXH, &GPB1, 1)) ret |= 1<<0;
	if (Gyroscope.IMU_Bus->Read(Gyroscope.I2C_Address, Gyroscope.RegMap->OutXL, &GPB2, 1)) ret |= 1<<1;
	AngularRate(0) = ((u16) ((GPB1<<8) | GPB2)) * Gyroscope.RegMap->Sensitivity.Current;
	if (Gyroscope.IMU_Bus->Read(Gyroscope.I2C_Address, Gyroscope.RegMap->OutYH, &GPB1, 1)) ret |= 1<<2;
	if (Gyroscope.IMU_Bus->Read(Gyroscope.I2C_Address, Gyroscope.RegMap->OutYL, &GPB2, 1)) ret |= 1<<3;
	AngularRate(1) = ((u16) ((GPB1<<8) | GPB2)) * Gyroscope.RegMap->.Sensitivity.Current;
	if (Gyroscope.IMU_Bus->Read(Gyroscope.I2C_Address, Gyroscope.RegMap->OutZH, &GPB1, 1)) ret |= 1<<4;
	if (Gyroscope.IMU_Bus->Read(Gyroscope.I2C_Address, Gyroscope.RegMap->OutZL, &GPB2, 1)) ret |= 1<<5;
	AngularRate(2) = ((u16) ((GPB1<<8) | GPB2)) * Gyroscope.RegMap->Sensitivity.Current;
	if (Gyroscope.IMU_Bus->Read(Gyroscope.I2C_Address, Gyroscope.RegMap->OutTemp, &GPB1, 1)) ret |= 1<<6;
	Gyroscope.TemperatureDelta = GPB1;
	return ret;
}

void Gyroscope_Update_SysStatus(){

}

int Gyroscope_Config(){
	int ret = 0;
	//TODO:[Optional] Implement Config Manager
	return ret;
}

struct S_Gyroscope{
	struct S_L3G4200D_Gyroscope *RegMap;
	struct S_I2C_Bus_Data *IMU_Bus;
	u8 I2C_Address;
	char TemperatureDelta;
	char SysStatus;
	long AngularRate[3];
	void (*Init) 		(struct S_I2C_Bus_Data *I2C_Bus, u8 Gyroscope_I2CAddr);
	char (*UpdateData) 	(void);
	void (*UpdateSysStatus)	(void);
	int	 (*Config) 		(void *ConfigPacket);
} Gyroscope = {
		.RegMap = &L3G4200D_Gyroscope,
		.Init	= &Gyroscope_Init,
		.UpdateData  	 = &Gyroscope_UpdateData,
		.UpdateSysStatus = &Gyroscope_Update_SysStatus,
		.Config			 = &Gyroscope_Config
};

#endif //#ifndef SCP_HwCtrl__10_DOF__Gyroscope_h
