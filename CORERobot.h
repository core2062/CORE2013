#include "CORESubsystem.h"
#include "COREJoystick.h"
#include <vector>
#ifndef COREROBOT_H
#define COREROBOT_H

class CORERobot{
	std::vector<CORESubsystem> subsystems;
	
public:
	CORERobot();
	
	void add(CORESubsystem& subsystem);
	
	std::vector<CORESubsystem>& get_subsystems(void);
	
	void teleop_init(void);
	
	void teleop(COREJoystick& joystick);
};

#endif
