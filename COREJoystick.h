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
	COREJoystickButton	blocker;
	COREJoystickButton  manPush;
	
	COREJoystickButton  quickturn;
	
public:
	COREJoystick(void):
	joystick1(1),
	joystick2(2),
	feedTrigger( &joystick2, 1),
	shooterRun( &joystick2, 2),
	pyramidSpeed( &joystick2, 6),
	shooterIncrease( &joystick2, 5),
	shooterDecrease( &joystick2, 3),
	blocker( &joystick2, 8),
	manPush( &joystick1, 7),
	quickturn( &joystick1, 5)
	{	}

	// Drive
	float driveLeft(void){return joystick1.GetRawAxis(2);};
	float driveRight(void){return joystick1.GetRawAxis(5);};
	float driveMag(void){return joystick1.GetRawAxis(2);};
	float driveKajRot(void){return joystick1.GetRawAxis(4);};
	float driveSteerX(void){return joystick1.GetRawAxis(4);};
	float driveSteerY(void){return joystick1.GetRawAxis(5);};
	bool driveQuickturn(void){return quickturn.Rise();};
	float driveQuickturnAxis(void){return joystick1.GetRawAxis(3);};
	bool autoRotLeft(void){return joystick1.GetRawButton(3);};
	bool autoRotRight(void){return joystick1.GetRawButton(2);};
//	bool pyramidDrive(void) {return joystick1.GetRawAxis(1)>0.66;};
	
	bool shooterOn(void){return shooterRun.Rise();};
	bool shooterDefault(void){return pyramidSpeed.Rise();};	
	bool shooterUp(void){return shooterIncrease.Rise();};
	bool shooterDown(void){return shooterDecrease.Rise();};
	bool shooterShoot(void){return feedTrigger.Get();};
	bool shooterBackwards(void){return joystick2.GetRawButton(12);};
	bool shooterManualBack(void){return manPush.Get();}; //back button in center of joystick
	bool shooterManStop(void){return manPush.Fall();}; //back button in center of joystick
	
	bool block(void){return blocker.Get();};
	bool blockDown(void){return joystick2.GetRawButton(7);};
};
		
#endif
