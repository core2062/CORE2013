#ifndef COREDRIVE_H
#define COREDRIVE_H

#import "WPILib.h"

// This class is used to connect a RobotDrive to a PIDController and still retain
// certain inherent functionality like inversion, scaling and limit checking
class COREDrivePIDGlue : public SpeedController{

	PIDController *PID;

public:

COREDrivePIDGlue( PIDController *PID ):
	PID( PID )
	{
	}
	
void Set(float speed, UINT8 syncGroup=0)
{
	PID->SetSetpoint(speed);
}
virtual float Get()  //questionable usefullness
{
	return PID->Get();
};

virtual void Disable(){}; // unsupported

}

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
	COREDrive::COREDrive(SpeedController &frontLeftMotor, SpeedController &rearLeftMotor,
				SpeedController &frontRightMotor, SpeedController &rearRightMotor
				):

			RobotDrive(frontLeftMotor, rearLeftMotor,
						frontRightMotor, rearRightMotor){
				
				// SetSafetyEnabled(false);
			}
	
	void EtherArcade(double mag, double rotate, double a, double b);
	void backupArcadeDrive(float moveValue, float rotateValue, bool squaredInputs = false);
};
#endif
