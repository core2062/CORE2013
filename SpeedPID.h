#ifndef SPEEDPID_H
#define SPEEDPID_H

#import "WPILib.h"

// This class is a PIDController that can be attached to a RobotDrive like a SpeedController 
// and still retain certain inherent functionality like inversion, scaling and limit checking
class SpeedPID : public PIDController, public SpeedController{

public:

	SpeedPID(float p, float i, float d, PIDSource *source, PIDOutput *output, float period = 0.05)
		:
		PIDController( p, i, d, source, output, period )
	{
	}
	
	void Set(float speed, UINT8 syncGroup=0)
	{
		SetSetpoint(speed); // if this doesn't compile try this.PIDController::SetSetpoint( speed )
	}
	virtual float Get()
	{
		return PIDController::Get(); // again, unsure of syntax also try this.PIDController::Get();
	}

	virtual void Disable(){
		PIDController::Disable();
	}
}

#endif