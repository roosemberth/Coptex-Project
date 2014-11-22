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
#include <eigen3/Eigen/Dense>
#include "IMU.h"
#include <math.h>

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

using namespace HwCtrl;

class IMU::Gyroscope{
	public:
		class C_L3G4200D{
			public:
				u8 Who_Am_I;
				u8 CtrlReg1;
				u8 CtrlReg2;
				u8 CtrlReg3;
				u8 CtrlReg4;
				u8 CtrlReg5;
				u8 Reference;
				u8 OutTemp;
				u8 StatusReg;
				u8 OutXL;
				u8 OutXH;
				u8 OutYL;
				u8 OutYH;
				u8 OutZL;
				u8 OutZH;
				u8 FifoCtrlReg;
				u8 FifoSrcReg;
				u8 Int1Cfg;
				u8 Int1Src;
				u8 Int1TshXH;
				u8 Int1TshXL;
				u8 Int1TshYH;
				u8 Int1TshYL;
				u8 Int1TshZH;
				u8 Int1TshZL;
				u8 Int1Duration;
				class C_Sensitivity{
					public:
						double S_250dps;
						double S_500dps;
						double S_2000dps;
						double Current;
						C_Sensitivity(){
							S_250dps = 0.00875 * M_PI;
							S_500dps = 0.0175 * M_PI;
							S_2000dps = 0.07 * M_PI;
							Current = S_250dps;
						}
				} Sensitivity;
				C_L3G4200D(){
					Who_Am_I = 0x0F;
					CtrlReg1 = 0x20;
					CtrlReg2 = 0x21;
					CtrlReg3 = 0x22;
					CtrlReg4 = 0x23;
					CtrlReg5 = 0x24;
					Reference = 0x25;
					OutTemp = 0x26;
					StatusReg = 0x27;
					OutXL = 0x28;
					OutXH = 0x29;
					OutYL = 0x2A;
					OutYH = 0x2B;
					OutZL = 0x2C;
					OutZH = 0x2D;
					FifoCtrlReg = 0x2E;
					FifoSrcReg = 0x2F;
					Int1Cfg = 0x30;
					Int1Src = 0x31;
					Int1TshXH = 0x32;
					Int1TshXL = 0x33;
					Int1TshYH = 0x34;
					Int1TshYL = 0x35;
					Int1TshZH = 0x36;
					Int1TshZL = 0x37;
					Int1Duration = 0x38;
				}
		} L3G4200D;
		Gyroscope(I2C_Bus &I2C_Interface, u8 Gyroscope_I2CAddr);
		bool UpdateData();
		char *SysStatus();
		char *SysTemperatureDelta();
		LinAlg::Vector3d *AngularRateP();
		bool config(void *ConfigPacket);
	private:
		u8 GPB1;																// General-Purpose Buffer 1
		u8 GPB2;																// General-Purpose Buffer 2
		u8 GyroI2CAddress;
		I2C_Bus *IMU_Bus;
		char TemperatureDelta;
		LinAlg::Vector3d<double> AngularRate;
		char Status;
};

bool IMU::Gyroscope::UpdateData(){
	GPB1 = 0;
	GPB2 = 0;
	AngularRate << 0, 0, 0;
	if (IMU_Bus->Read(GyroI2CAddress, L3G4200D.OutXH, &GPB1, 1)) return true;
	if (IMU_Bus->Read(GyroI2CAddress, L3G4200D.OutXL, &GPB2, 1)) return true;
	AngularRate(0) = ((u16) ((GPB1<<8) | GPB2)) * L3G4200D.Sensitivity.Current;
	if (IMU_Bus->Read(GyroI2CAddress, L3G4200D.OutYH, &GPB1, 1)) return true;
	if (IMU_Bus->Read(GyroI2CAddress, L3G4200D.OutYL, &GPB2, 1)) return true;
	AngularRate(1) = ((u16) ((GPB1<<8) | GPB2)) * L3G4200D.Sensitivity.Current;
	if (IMU_Bus->Read(GyroI2CAddress, L3G4200D.OutZH, &GPB1, 1)) return true;
	if (IMU_Bus->Read(GyroI2CAddress, L3G4200D.OutZL, &GPB2, 1)) return true;
	AngularRate(2) = ((u16) ((GPB1<<8) | GPB2)) * L3G4200D.Sensitivity.Current;
	if (IMU_Bus->Read(GyroI2CAddress, L3G4200D.OutTemp, &GPB1, 1)) return true;
	TemperatureDelta = GPB1;
	return false;
}

IMU::Gyroscope::Gyroscope(I2C_Bus &I2C_Interface, u8 Gyroscope_I2CAddr){
	GyroI2CAddress = Gyroscope_I2CAddr;
	IMU_Bus = I2C_Interface;
	AngularRate << 0, 0, 0;
	TemperatureDelta = 0;
	Status = 0;
	GPB1 = 0;
	GPB2 = 0;
	// if (IMU_Bus->Read(GyroI2CAddress, L3G4200D.Who_Am_I, &GPB1, 1)!=0xD3) TODO:[Critical] Implement Error-Notifying Mechanism
	GPB1 = 0 | L3G4200D_CtrlReg1_PD | L3G4200D_CtrlReg1_Xen | L3G4200D_CtrlReg1_Yen | L3G4200D_CtrlReg1_Zen;
	IMU_Bus->Write(GyroI2CAddress, L3G4200D.CtrlReg1, &GPB1, 1);

	GPB1 = 0;
	IMU_Bus->Write(GyroI2CAddress, L3G4200D.CtrlReg2, &GPB1, 1);

	GPB1 = 0 | L3G4200D_CtrlReg3_I2DRDY;
	IMU_Bus->Write(GyroI2CAddress, L3G4200D.CtrlReg3, &GPB1, 1);

	GPB1 = 0 | L3G4200D_Sensitivity_S_250dps;
	L3G4200D.Sensitivity.Current = L3G4200D.Sensitivity.S_250dps;
	IMU_Bus->Write(GyroI2CAddress, L3G4200D.CtrlReg4, &GPB1, 1);

	GPB1 = 0;
	IMU_Bus->Write(GyroI2CAddress, L3G4200D.CtrlReg5, &GPB1, 1);

	UpdateData();
}

char *IMU::Gyroscope::SysStatus(){
	return &Status;
}

char *IMU::Gyroscope::SysTemperatureDelta(){
	return &TemperatureDelta;
}

LinAlg::Vector3d *IMU::Gyroscope::AngularRateP(){
	return &AngularRate;
}

bool IMU::Gyroscope::config(void *ConfigPacket){
	//TODO:[Optional] Implement Config Manager
	return false;
}

#endif //#ifndef SCP_HwCtrl__10_DOF__Gyroscope_h
