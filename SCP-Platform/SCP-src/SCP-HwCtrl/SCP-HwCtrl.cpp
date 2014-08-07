/*
 * "Coptex Project Hardware Control Subsystem" - Coptex Project Hardware Control
 *
 * Copyright (C) 2013-2015 Roosemberth Palacios <roosemberth@roosemberth.usr.sh>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2.
 *
 */
#include "USB-Pololu-Maestro/Maestro-Definitions.h"
#include "SCP-HwCtrl.h"

namespace HwCtrl{
	void C_MaestroUpdateQueue::EnqueuePositionUpdate(char Channel, unsigned short Position){
		this->UpdateQueue.UpdatePending |= 1<<Channel;
		this->UpdateQueue.Position[Channel-1] = Position;
	}
	unsigned short C_MaestroUpdateQueue::QueryPositionUpdate(char Channel){
		return (this->UpdateQueue.UpdatePending & 1<<Channel)?this->UpdateQueue.Position[Channel-1]:0;
	}
	int C_MaestroUpdateQueue::FlushPendingUpdates(){
		//TODO: Implement Maestro Comunication Platform
		return 0;
	}
}
