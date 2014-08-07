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
#ifndef SCP_HwCtrl_h
#define SCP_HwCtrl_h

namespace HwCtrl{
	class C_MaestroUpdateQueue{
		public:
			void EnqueuePositionUpdate(char Channel, unsigned short Position);
			unsigned short QueryPositionUpdate(char Channel);
			int FlushPendingUpdates();
		private:
			struct S_MaestroUpdatePositionQueue{
				char Device[];
				unsigned int UpdatePending;			// Bitwise Status 'Register' UpdatePending
				unsigned short Position[24];		// New Position
			} UpdateQueue;
	};

	C_MaestroUpdateQueue MaestroUpdateQueue;

};

#endif // #ifndef SCP_HwCtrl_h
