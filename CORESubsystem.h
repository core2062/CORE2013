#include "WPILib.h"
#include "COREJoystick.h"
#include <string>
#ifndef CORESUBSYSTEM_H
#define CORESUBSYSTEM_H

class CORESubsystem{
	public:
	
	std::string name;
	CORESubsystem(void);
	
	virtual ~CORESubsystem(void){};	// Suppresses GNU GCC warning. Can be removed under GCC version 4.3
	
	// Called before loop at start of Teleop period
	virtual void teleop_init(void);
	
	//Called sequentially during loop, interleaved with other subsystems
	virtual void teleop_joystick(COREJoystick& joystick);
	virtual void teleop_main(void);
	virtual void teleop_motors(void);
};

#endif
