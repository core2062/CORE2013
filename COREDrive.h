#ifndef COREDRIVE_H
#define COREDRIVE_H

#import "WPILib.h"

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
	
	PIDController *leftPID;
	PIDController *rightPID;
	
public:
	COREDrive::COREDrive(SpeedController &frontLeftMotor, SpeedController &rearLeftMotor,
				SpeedController &frontRightMotor, SpeedController &rearRightMotor,
				PIDController *LeftPID, PIDController *RightPID):

			RobotDrive(frontLeftMotor, rearLeftMotor,
						frontRightMotor, rearRightMotor){
				leftPID = LeftPID;
				rightPID = RightPID;
				SetSafetyEnabled(false);
			}
	
	void EtherArcade(double mag, double rotate, double a, double b);
	void ArcadeDrive(float moveValue, float rotateValue, bool squaredInputs = false);
};
#endif
