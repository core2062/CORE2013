#include "WPILib.h"
#ifndef COREJOYSTICK_H
#define COREJOYSTICK_H

class COREJoystickButton {
	Joystick	*joystick;
	int			input;
	bool		state;
	bool		oldState;

public:
	COREJoystickButton( Joystick *, int );
	bool Get();	// returns current state
	bool Rise(); // returns true on rising edge
	bool Fall(); // returns false on rising edge
};

class COREJoystick {
	
	Joystick joystick1;
	Joystick joystick2;
	
	COREJoystickButton	feedTrigger;
	COREJoystickButton	shooterRun;
	
public:
	COREJoystick(void):
	joystick1(1),
	joystick2(2),
	feedTrigger( &joystick2, 1),
	shooterRun( &joystick2, 2){}

	// Drive
	float driveLeft(void){return joystick1.GetRawAxis(1);};
	float driveRight(void){return joystick1.GetRawAxis(3);};
	

	bool shooterOn(void){return shooterRun.Rise();};
	bool shooterZero(void){return joystick2.GetRawButton(5);};
	bool shooterUp(void){return joystick2.GetRawButton(4);};
	bool shooterDown(void){return joystick2.GetRawButton(3);};
	bool shooterShoot(void){return feedTrigger.Rise();};
	
	bool climbFull(void){return joystick2.GetRawButton(6);};
	bool climbHalf(void){return joystick2.GetRawButton(7);};
	bool climbNormal(void){return joystick2.GetRawButton(8);};
	bool climbTilt(void){return joystick2.GetRawButton(9);};

};
		
#endif
