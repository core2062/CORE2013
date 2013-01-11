#include "WPILib.h"
#ifndef COREJOYSTICK_H
#define COREJOYSTICK_H

class COREJoystick {
	
	Joystick joystick1;
	Joystick joystick2;
	
public:
	COREJoystick(void):
	joystick1(1),
	joystick2(2){}
};

#endif
