#include "CORESubsystemRobot.h"
#include "LiftSubsystem.h"

LiftSubsystem::LiftSubsystem(void):
motorShooter(9),
motorTilter(9)
{}

void LiftSubsystem::teleopInit(void){
	
}

void LiftSubsystem::teleopInput(COREJoystick& joystick)
{
	speedHalf = joystick.liftHalf();
	speedFull = joystick.liftFull();
	isTilting = joystick.liftTilt();
}

void LiftSubsystem::teleopLogic(void){
	currentSpeed = getLiftSpeed();
}

void LiftSubsystem::teleopOutput(void){
	motorShooter.Set(currentSpeed);
	motorTilter.Set(isTilting? .9 : 0);
}
float LiftSubsystem::getLiftSpeed()
{
	return (speedFull ? 0.8 : 0.0);
}
