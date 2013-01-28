#include "CORESubsystemRobot.h"
#include "DriveSubsystem.h"

float deadband(float value, float range = .1);

DriveSubsystem::DriveSubsystem(void):
	FLDrive(3),
	RLDrive(4),
	FRDrive(5),
	RRDrive(6),
	
	drive(FLDrive,RLDrive,FRDrive,RRDrive)
{
	drive.SetInvertedMotor(RobotDrive::kFrontLeftMotor,true);
	drive.SetInvertedMotor(RobotDrive::kFrontRightMotor,true);
	drive.SetInvertedMotor(RobotDrive::kRearLeftMotor,true);
	
	driveArcade = false;
}
std::string DriveSubsystem::name(void){
	return "Drive";
}

void DriveSubsystem::teleopInit(void){
	SmartDashboard::PutBoolean("Arcade Drive", false);

}

void DriveSubsystem::teleopInput(COREJoystick& joystick){
	driveRight = joystick.driveRight();
	driveLeft = joystick.driveLeft();
	driveMag = joystick.driveMag();
	driveRotate = joystick.driveRotate();
	
	driveArcade = SmartDashboard::GetBoolean("Arcade Drive");
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

Jaguar* DriveSubsystem::getFLDrive(void){
	return &FLDrive;
}
Jaguar* DriveSubsystem::getRLDrive(void){
	return &RLDrive;
}
Jaguar* DriveSubsystem::getFRDrive(void){
	return &FRDrive;
}
Jaguar* DriveSubsystem::getRRDrive(void){
	return &RRDrive;
}
