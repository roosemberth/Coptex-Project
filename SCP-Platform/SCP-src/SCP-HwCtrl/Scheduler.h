/*
 * "Coptex Project Hardware Control Update Scheduler" - Coptex Project Hardware Control
 *
 * Copyright (C) 2013-2015 Roosemberth Palacios <roosemberth@roosemberth.usr.sh>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2.
 *
 */

#include "USB-Pololu-Maestro/Maestro-Definitions.h"

struct S_HwCtrlPositionQueue{
	char Device[];
	unsigned int UpdatePending;			// Bitwise Status 'Register' UpdatePending
	unsigned short Position[24];		// New Position
} HwCtrlPositionQueue;

void HwCtrlEnqueuePositionUpdate(char Channel, unsigned short Position){
	HwCtrlPositionQueue.UpdatePending |= 1<<Channel;
	HwCtrlPositionQueue.Position[Channel-1] = Position;
}
