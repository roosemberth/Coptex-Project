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

#include "../../SCP-Include/SCP-Config.h"
#include "../HwPlatforms/I2C-Bus.h"
#include <eigen3/Eigen/Dense>
#include "Gyroscope.h"

using namespace HwCtrl;

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

IMU::Gyroscope::Gyroscope(I2C_Bus &I2C_Interface){
	GyroI2CAddress = SCP_Gyroscope_I2CAddr;
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
