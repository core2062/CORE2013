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
	float driveLeft(void){return joystick1.GetRawAxis(1);};
	float driveRight(void){return joystick1.GetRawAxis(3);};
	
	bool shooterOn(void){return joystick2.GetRawButton(2);};
	bool shooterZero(void){return joystick2.GetRawButton(5);};
	bool shooterUp(void){return joystick2.GetRawButton(4);};
	bool shooterDown(void){return joystick2.GetRawButton(3);};
	bool shooterShoot(void){return joystick2.GetRawButton(1);};
};
		
#endif
