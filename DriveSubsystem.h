#include "WPILib.h"
#include "CORERobot.h"

class DriveSubsystem : CORESubsystem{
	RobotDrive drive;
	
	float drive_right;
	float drive_left;
public:
	DriveSubsystem(void):
		drive(1,2,3,4)
	{}
	
	void teleop_init(){
		
	}
	
	void teleop_inputs(COREJoystick& joystick){
		drive_right = joystick.drive_right();
		drive_left = joystick.drive_left();
	}
	
	void teleop_logic(){
		//nope
	}
	
	void teleop_outputs(){
		drive.TankDrive(drive_left, drive_right);
	}
};
