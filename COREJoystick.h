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

	// Drive
	float drive_left(void){return joystick1.GetRawAxis(1);};
	float drive_right(void){return joystick1.GetRawAxis(3);};
};

#endif
