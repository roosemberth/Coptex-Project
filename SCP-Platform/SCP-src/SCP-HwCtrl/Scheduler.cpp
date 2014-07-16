#include "Scheduler.h"

void initHwScheduler(){
	HwCtrlPositionQueue.Device = "/dev/Maestro0";
	HwCtrlPositionQueue.UpdatePending = 0;
}

