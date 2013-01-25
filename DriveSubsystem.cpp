#include "CORESubsystemRobot.h"
#include "DriveSubsystem.h"

float deadband(float value, float range = .1);

DriveSubsystem::DriveSubsystem(void):
	drive(3,4,5,6)
{
	drive.SetInvertedMotor(RobotDrive::kFrontLeftMotor,true);
	drive.SetInvertedMotor(RobotDrive::kFrontRightMotor,true);
	drive.SetInvertedMotor(RobotDrive::kRearLeftMotor,true);
	
	//initialize bool
	driveArcade = false;
}
std::string DriveSubsystem::name(void){
	return "Drive";
}

void DriveSubsystem::teleopInit(void){
	
}

void DriveSubsystem::teleopInput(COREJoystick& joystick){
	driveRight = joystick.driveRight();
	driveLeft = joystick.driveLeft();
	driveMag = joystick.driveMag();
	driveRotate = joystick.driveRotate();
	driveArcade = joystick.driveArcade();
}

void DriveSubsystem::teleopLogic(void){
	deadband(driveRight);
	deadband(driveLeft);
	deadband(driveMag);
	deadband(driveRotate);
}

void DriveSubsystem::teleopOutput(void){
	if(driveArcade){
		drive.ArcadeDrive(driveMag, driveRotate);
	}
	else{
		drive.TankDrive(driveLeft, driveRight);
	}
}

float deadband(float value, float range){
	if(std::abs(value) < range){
		return 0;
	}
	return value;
}
