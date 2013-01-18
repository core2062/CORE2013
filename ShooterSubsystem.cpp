#include "CORESubsystemRobot.h"
#include "ShooterSubsystem.h"


ShooterSubsystem::ShooterSubsystem(void):
shooterMotor(8),
hopperSwitch(1)
//shooterEncoder(1)
{}

std::string ShooterSubsystem::name(void)
{
	return "Shooter";
}

void ShooterSubsystem::teleopInit(void)
{
//	shooterEncoder.Start();
}

void ShooterSubsystem::teleopInput(COREJoystick& joystick){
/*
 * button to shoot
 * + speed button
 * - speed button
 * reset speed button
 * 
 * encoder value
 * hopper switch value
 */
	pyramidSpeed = joystick.shooterZero();
	up = joystick.shooterUp();
	down = joystick.shooterDown();
	shoot = joystick.shooterShoot();
	shooterOn = joystick.shooterOn();
}

void ShooterSubsystem::teleopLogic(void){
	shooterInc = 0.05;
	pyramidSpeed = .5;
	if (!oldPyramidSpeed && pyramidSpeed) {
		shooterValue = shooterDefault;
	}
	if (!oldUp && up) {
		shooterValue += shooterInc;
	}
	if (!oldDown && down) {
		shooterValue -= shooterInc;
	}
	
	oldPyramidSpeed = pyramidSpeed;
	oldUp = up;
	oldDown = down;
	if (shoot) {
		//placeholder
	}
	if (shooterOn) {
		shooterOutput = shooterValue;
	}
	else {
		shooterOutput = 0;
	}
	
}

void ShooterSubsystem::teleopOutput(void){
	shooterMotor.Set(shooterOutput);
}

