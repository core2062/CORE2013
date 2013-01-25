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
	
	bool arcade;
	
	
public:
	COREJoystick(void):
	joystick1(1),
	joystick2(2),
	feedTrigger( &joystick2, 1),
	shooterRun( &joystick2, 2),
	pyramidSpeed( &joystick2, 5),
	shooterIncrease( &joystick2, 4),
	shooterDecrease( &joystick2, 3){
		arcade = false;
	}

	// Drive
	float driveLeft(void){return joystick1.GetRawAxis(2);};
	float driveRight(void){return joystick1.GetRawAxis(5);};
	float driveMag(void){return joystick1.GetRawAxis(5);};
	float driveRotate(void){return joystick1.GetRawAxis(4);};
	
	bool shooterOn(void){return shooterRun.Rise();};
	bool shooterDefault(void){return pyramidSpeed.Rise();};
	bool shooterUp(void){return shooterIncrease.Rise();};
	bool shooterDown(void){return shooterDecrease.Rise();};
	bool shooterShoot(void){return feedTrigger.Rise();};
	
	bool climbFull(void){return joystick2.GetRawButton(6);};
	bool climbHalf(void){return joystick2.GetRawButton(7);};
	bool climbTilt(void){return joystick2.GetRawButton(9);};
	bool climbDeTilt(void){return joystick2.GetRawButton(10);};
	
	
	void driveArcade(bool n){arcade=n;};
	bool driveArcade(void){return arcade;};
};
		
#endif
