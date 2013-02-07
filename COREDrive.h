#ifndef COREDRIVE_H
#define COREDRIVE_H

#import "WPILib.h"

class COREDrive : public RobotDrive{
public:
	COREDrive::COREDrive(SpeedController &frontLeftMotor, SpeedController &rearLeftMotor,
			SpeedController &frontRightMotor, SpeedController &rearRightMotor):
			RobotDrive(frontLeftMotor, rearLeftMotor,
						frontRightMotor, rearRightMotor){
		
	}
	
	void EtherArcade(double mag, double rotate, double a, double b);
	void ArcadeDrive(float moveValue, float rotateValue, bool squaredInputs = false);
};
#endif
