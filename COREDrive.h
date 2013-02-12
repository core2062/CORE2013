#ifndef COREDRIVE_H
#define COREDRIVE_H

#import "WPILib.h"

// class to support driving two jaguars from one PIDController
class COREDrivePIDOut : public PIDOutput{
	Jaguar *front;
	Jaguar *rear;
public:
	
	COREDrivePIDOut(Jaguar *f, Jaguar *r){
		front = f;
		rear = r;
	};
	void PIDWrite (float output);
};

class COREDrive : public RobotDrive{
		
public:
	COREDrive::COREDrive(SpeedController &leftMotor,
				SpeedController &rightMotor
				):
			RobotDrive(leftMotor,
						rightMotor){
				
				// SetSafetyEnabled(false);
			}
	
	void EtherArcade(double mag, double rotate, double a, double b);
	void backupArcadeDrive(float moveValue, float rotateValue, bool squaredInputs = false);
};
#endif
