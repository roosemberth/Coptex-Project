#ifndef SCP_HwCtrl_h
#define SCP_HwCtrl_h
/*
 * "Coptex Project Hardware Control Subsystem" - Coptex Project Hardware Control
 *
 * Copyright (C) 2013-2015 Roosemberth Palacios <roosemberth@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2.
 *
 */

#include "../../SCP-Include/SCP-Config.h"
#include <boost/numeric/ublas/vector.hpp>


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
	class IMU;

	C_MaestroUpdateQueue MaestroUpdateQueue;

	boost::numeric::ublas::vector<double float> Acceleration (3);


};

#endif // #ifndef SCP_HwCtrl_h
