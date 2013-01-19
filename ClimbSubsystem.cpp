#include "CORESubsystemRobot.h"
#include "ClimbSubsystem.h"

ClimbSubsystem::ClimbSubsystem(void):
climberMotor(9),
camMotor(7) //the motor for tilting the robot
{}

void ClimbSubsystem::teleopInit(void){
	
}

void ClimbSubsystem::teleopInput(COREJoystick& joystick)
{
	speedHalf = joystick.climbHalf();
	speedFull = joystick.climbFull();
	isTilting = joystick.climbTilt();
}

void ClimbSubsystem::teleopLogic(void){
	currentSpeed = getClimbSpeed();
}

void ClimbSubsystem::teleopOutput(void){
	climberMotor.Set(currentSpeed);
	camMotor.Set(isTilting? .9 : 0);
}
float ClimbSubsystem::getClimbSpeed()
{
	return (speedFull ? 0.8 : 0.0);
}
