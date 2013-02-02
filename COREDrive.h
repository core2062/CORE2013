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
	void ColinArcade(double mag, double rotate);
	
	void EtherArcade(double mag, double rotate, double a, double b);
};
#endif
