#include "CORESubsystemRobot.h"
#include "ClimbSubsystem.h"

static Segment steps[] = {	
		Segment(.3,2),
		Segment(1,7),
		Segment(.3,8),
		Segment(1,9),
		Segment(.3,10),
		Segment(-.3,8),
		Segment(-1,.3),
		Segment(-.3,2),
		Segment(-1,1),
		Segment(-.3,0),
		Segment(.3,2),
		Segment(1,7),
		Segment(.3,8),
		Segment(1,9),
		Segment(.3,10)
	};

ClimbSubsystem::ClimbSubsystem(void):
climbMotor(CORERobot::CLIMBER),
tiltMotor(CORERobot::TILTER), //the motor for tilting the robot

tiltTopLimit(CORERobot::TILT_LIMIT_TOP),
tiltBottomLimit(CORERobot::TILT_LIMIT_BOTTOM),
climbTopLimit(CORERobot::CLIMB_LIMIT_TOP),
climbBottomLimit(CORERobot::CLIMB_LIMIT_BOTTOM),
climbEncoder(CORERobot::CLIMB_ENC_A, CORERobot::CLIMB_ENC_B)
{
}

void ClimbSubsystem::teleopInit(void){
	
}

void ClimbSubsystem::teleopInput(COREJoystick& joystick)
{
	speedHalf = joystick.climbHalf();
	speedFull = joystick.climbFull();
	isTilting = (!tiltLimit.Get()) and joystick.climbTilt();
	isDeTilting = joystick.climbDeTilt();
	// cout << (isTilting? "im tilting":"no tilt 4 u") << endl; 
}

void ClimbSubsystem::teleopLogic(void){
	currentSpeed = getClimbSpeed();
}

void ClimbSubsystem::teleopOutput(void){
	climbMotor.Set(currentSpeed);
	
	float tiltSpeed;
	
	if (isDeTilting)
		tiltSpeed = -.5;
	else
		tiltSpeed = isTilting? .9 : 0;
	
	tiltMotor.Set( tiltSpeed );
}

float ClimbSubsystem::getClimbSpeed()
{
	return (speedFull ? 0.8 : 0.0);
}
