#include "CORESubsystemRobot.h"
#include "DriveSubsystem.h"

float deadband(float value, float range = .1);

DriveSubsystem::DriveSubsystem(void):
	drive(6,7,8,10)
{}
std::string DriveSubsystem::name(void){
	return "Drive";
}

void DriveSubsystem::teleopInit(void){
	
}

void DriveSubsystem::teleopInput(COREJoystick& joystick){
	driveRight = joystick.driveRight();
	driveLeft = joystick.driveLeft();
}

void DriveSubsystem::teleopLogic(void){
	deadband(driveRight);
	deadband(driveLeft);
}

void DriveSubsystem::teleopOutput(void){
	drive.TankDrive(driveLeft, driveRight);
}

float deadband(float value, float range){
	if(std::abs(value) < range){
		return 0;
	}
	return value;
}
