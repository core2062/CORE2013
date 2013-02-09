#include "CORESubsystemRobot.h"
#include "ClimbSubsystem.h"

ClimbSubsystem::ClimbSubsystem(void):
climberMotor(CORERobot::CLIMBER),
camMotor(CORERobot::TILTER), //the motor for tilting the robot
tiltLimit(CORERobot::TILT_LIMIT)
{}

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
	climberMotor.Set(currentSpeed);
	
	float tiltSpeed;
	
	if (isDeTilting)
		tiltSpeed = -.5;
	else
		tiltSpeed = isTilting? .9 : 0;
	
	camMotor.Set( tiltSpeed );
}

float ClimbSubsystem::getClimbSpeed()
{
	return (speedFull ? 0.8 : 0.0);
}
