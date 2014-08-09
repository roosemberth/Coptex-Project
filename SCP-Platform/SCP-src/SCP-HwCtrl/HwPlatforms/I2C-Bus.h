#ifndef SCP_HwCtrl__Platform__I2C_Bus_h
#define SCP_HwCtrl__Platform__I2C_Bus_h
/*
 * "I2C Platform Interface" - Coptex Project Hardware Control
 *
 * Copyright (C) 2013-2015 Roosemberth Palacios <roosemberth@gmail.com>
 * Special Thanks to llongeri
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2.
 *
 */

#include "../../SCP-Include/SCP-Config.h"

class I2C_Bus{
	public:
		I2C_Bus(const char *Device);
		bool Write(u16 Addr, u8 RegAddr, u8 *Data, char Bytes);		// return 1 on Error
		bool Read(u16 Addr, u8 RegAddr, u8 *Data, char Bytes);		// return 1 on Error
	private:
		struct i2c_rdwr_ioctl_data Queue;
		const char Dev[];
		int handle;
};

#endif // #ifndef SCP_HwCtrl__Platform__I2C_Bus_h
