#include "WPILib.h"
#include "CORESubsystemRobot.h"

class DriveSubsystem : CORESubsystem{
	RobotDrive drive;
	
	float driveRight;
	float driveLeft;
public:
	DriveSubsystem(void):
		drive(1,2,3,4)
	{}
	
	void teleopInit(){
		
	}
	
	void teleopInputs(COREJoystick& joystick){
		driveRight = joystick.driveRight();
		driveLeft = joystick.driveLeft();
	}
	
	void teleopLogic(){
		deadband(driveRight);
		deadband(driveLeft);
	}
	
	void teleopOutputs(){
		drive.TankDrive(driveLeft, driveRight);
	}
	float deadband(float value, float range = .1){
		if(abs(value) < range){
			return 0;
		}
		return value;
	}
};
