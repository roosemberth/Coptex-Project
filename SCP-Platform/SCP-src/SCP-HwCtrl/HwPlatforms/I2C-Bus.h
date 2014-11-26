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

#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <fcntl.h>

typedef unsigned char 	u8;
typedef unsigned short 	u16;
typedef unsigned int 	u32;

void I2C_Bus_Init(const char *Device){
	char GPC;														// General Purpose Counter
	int io;
	I2C_Bus_Data.Handle = -1;
	I2C_Bus_Data.Dev = Device;
	io = -1;
	while (++GPC <= 10 && I2C_Bus_Data.Handle < 0)
		I2C_Bus_Data.Handle = open(I2C_Bus_Data.Dev, O_RDWR);
	GPC=0;
	// ioctl(handle, I2C_TENBIT, address_config);
	while (++GPC <= 10 && io!=0) io = ioctl(I2C_Bus_Data.Handle, I2C_TENBIT, 0);
}

int I2C_Bus_Read(u16 Addr, u8 RegAddr, u8 *Data, char Bytes){
	struct i2c_msg msg[2];

	I2C_Bus_Data.Queue.nmsgs = 2;
	I2C_Bus_Data.Queue.msgs = msg;

	I2C_Bus_Data.Queue.msgs[0].addr = Addr;
	I2C_Bus_Data.Queue.msgs[0].len = 1;
	I2C_Bus_Data.Queue.msgs[0].flags = 0;
	I2C_Bus_Data.Queue.msgs[0].buf = &RegAddr;

	I2C_Bus_Data.Queue.msgs[1].addr = Addr;
	I2C_Bus_Data.Queue.msgs[1].len = Bytes;
	I2C_Bus_Data.Queue.msgs[1].flags = I2C_M_RD;
	I2C_Bus_Data.Queue.msgs[1].buf = Data;

	return ioctl(I2C_Bus_Data.Handle, I2C_RDWR, &I2C_Bus_Data.Queue)!=2;
}

int I2C_Bus_Write(u16 Addr, u8 RegAddr, u8 *Data, char Bytes){
    char GPC;														// General-Purpose Counter
	struct i2c_msg msg[1];

	u8 Buffer[Bytes + 1];
    Buffer[0] = RegAddr;
    for (GPC=0; GPC<Bytes; ++GPC){
        Buffer[1+GPC] = Data[GPC];
    }
    I2C_Bus_Data.Queue.nmsgs = 1;
    I2C_Bus_Data.Queue.msgs = msg;

    I2C_Bus_Data.Queue.msgs[0].addr = Addr;
    I2C_Bus_Data.Queue.msgs[0].len = Bytes+1;
    I2C_Bus_Data.Queue.msgs[0].flags = 0;
    I2C_Bus_Data.Queue.msgs[0].buf = Buffer;

	return ioctl(I2C_Bus_Data.Handle, I2C_RDWR, &I2C_Bus_Data.Queue)!=Bytes;
}

struct S_I2C_Bus_Data{
	struct i2c_rdwr_ioctl_data Queue;
	char Dev[];
	int Handle;
	void (*Init)	(const char *Device);
	void (*Read)	(u16 Addr, u8 RegAddr, u8 *Data, char Bytes);
	void (*Write)	(u16 Addr, u8 RegAddr, u8 *Data, char Bytes);
} I2C_Bus_Data = {
		.Init = &I2C_Bus_Init,
		.Read = &I2C_Bus_Read,
		.Write = &I2C_Bus_Write
};

#endif // #ifndef SCP_HwCtrl__Platform__I2C_Bus_h
