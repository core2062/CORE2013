#include "WPILib.h"
#ifndef COREJOYSTICK_H
#define COREJOYSTICK_H

class COREJoystickButton {
	Joystick	*joystick;
	int			input;
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
	COREJoystickButton	pyramidSpeed;
	COREJoystickButton	shooterIncrease;
	COREJoystickButton	shooterDecrease;
	
	
public:
	COREJoystick(void):
	joystick1(1),
	joystick2(2),
	feedTrigger( &joystick2, 1),
	shooterRun( &joystick2, 2),
	pyramidSpeed( &joystick2, 6),
	shooterIncrease( &joystick2, 5),
	shooterDecrease( &joystick2, 3){
	}

	// Drive
	float driveLeft(void){return joystick1.GetRawAxis(2);};
	float driveRight(void){return joystick1.GetRawAxis(5);};
	float driveKajMag(void){return joystick1.GetRawAxis(2);};
	float driveKajRot(void){return joystick1.GetRawAxis(4);};
	bool autoRotLeft(void){return joystick1.GetRawButton(3);};
	bool autoRotRight(void){return joystick1.GetRawButton(2);};
	bool pyramidDrive(void) {return joystick1.GetRawAxis(1)>0.66;};
	
	bool shooterOn(void){return shooterRun.Rise();};
	bool shooterDefault(void){return pyramidSpeed.Rise();};	
	bool shooterUp(void){return shooterIncrease.Rise();};
	bool shooterDown(void){return shooterDecrease.Rise();};
	bool shooterShoot(void){return feedTrigger.Get();};
	bool shooterBackwards(void){return joystick2.GetRawButton(12);};
	
	bool climb(void){return joystick1.GetRawButton(4);};
	bool climbTilt(void){return joystick2.GetRawButton(7);};
	bool climbDetilt(void){return joystick2.GetRawButton(11);};
	bool climbReset(void){return joystick1.GetRawButton(5);};
	float rawClimb(void){return -joystick2.GetRawAxis(2);};
};
		
#endif
