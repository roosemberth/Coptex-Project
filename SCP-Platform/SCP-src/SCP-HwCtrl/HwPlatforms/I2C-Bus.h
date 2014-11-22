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

#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

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

I2C_Bus::I2C_Bus(const char *Device){
	char GPC;														// General Purpose Counter
	int io;
	handle = -1;
	Dev = Device;
	io = -1;
	while (++GPC <= 10 && handle < 0) handle = open(Dev, O_RDWR);
	GPC=0;
	while (++GPC <= 10 && io!=0) io = ioctl(handle, I2C_TENBIT, 0);	// ioctl(handle, I2C_TENBIT, address_config);
}

bool I2C_Bus::Write(u16 Addr, u8 RegAddr, u8 *Data, char Bytes){
    char GPC;														// General-Purpose Counter
	struct i2c_msg msg[1];

	u8 Buffer[Bytes + 1];
    Buffer[0] = RegAddr;
    for (GPC=0; GPC<Bytes; ++GPC){
        Buffer[1+GPC] = Data[GPC];
    }
    Queue.nmsgs = 1;
    Queue.msgs = msg;

    Queue.msgs[0].addr = Addr;
    Queue.msgs[0].len = Bytes+1;
    Queue.msgs[0].flags = 0;
    Queue.msgs[0].buf = Buffer;

	return ioctl(handle, I2C_RDWR, &Queue)!=Bytes;
}

bool I2C_Bus::Read(u16 Addr, u8 RegAddr, u8 *Data, char Bytes){
	struct i2c_msg msg[2];

    Queue.nmsgs = 2;
    Queue.msgs = msg;

    Queue.msgs[0].addr = Addr;
    Queue.msgs[0].len = 1;
    Queue.msgs[0].flags = 0;
    Queue.msgs[0].buf = &RegAddr;

    Queue.msgs[1].addr = Addr;
    Queue.msgs[1].len = Bytes;
    Queue.msgs[1].flags = I2C_M_RD;
    Queue.msgs[1].buf = Data;

	return ioctl(handle, I2C_RDWR, &Queue)!=2;
}



#endif // #ifndef SCP_HwCtrl__Platform__I2C_Bus_h
