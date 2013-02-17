#include "CORESubsystemRobot.h"
#include "ClimbSubsystem.h"


float zero = 0.0;
float pinf = 1.0 / zero;

static Segment steps[] = {	
		Segment(.5,2),
		Segment(1,7),
		Segment(.5,8),
//		Segment(1,9),
		Segment(.5,10),
		Segment(-.5,8),
		Segment(-1,3),
		Segment(-.5,2),
//		Segment(-1,1),
		Segment(-.5,0),
		Segment(.5,2),
		Segment(1,7),
		Segment(.5,8),
//		Segment(1,9),
		Segment(.5,10),
		Segment(0,pinf)
	};

ClimbSubsystem::ClimbSubsystem(void):
climbMotor(CORERobot::CLIMBER),
tiltMotor(CORERobot::TILTER), //the motor for tilting the robot

tiltPosLimit(CORERobot::TILT_LIMIT_POSITIVE),
tiltNegLimit(CORERobot::TILT_LIMIT_NEGATIVE),
climbTopLimit(CORERobot::CLIMB_LIMIT_TOP),
climbBottomLimit(CORERobot::CLIMB_LIMIT_BOTTOM),
climbEncoder(CORERobot::CLIMB_ENC_A, CORERobot::CLIMB_ENC_B)
{
	stepCount = 0;
	climbEncoder.SetDistancePerPulse(.1/(360));
	climbEncoder.Start();
	climbEncoder.Reset();
}

void ClimbSubsystem::teleopInit(void){
	
}

void ClimbSubsystem::teleopInput(COREJoystick& joystick)
{
	tilting = joystick.climbTilt(); 
	isDeTilting = joystick.climbDetilt();
	climbing = joystick.climb();
	reset = joystick.climbReset();
}

void ClimbSubsystem::teleopLogic(void){
	if (climbBottomLimit.Get()){
		climbEncoder.Reset();
	}
	if (climbing){
		if(steps[stepCount].speed > 0){
			if(climbEncoder.GetDistance() > steps[stepCount].pos){
				++stepCount;
			}	
		}else{
			if(climbEncoder.GetDistance() < steps[stepCount].pos){
				++stepCount;
			}
		}
		
		currentSpeed = steps[stepCount].speed;
	}else if (reset){
		stepCount = 0;
		currentSpeed = -.5;
	}else{
		currentSpeed = 0;
	}
	cout << stepCount << ": " << climbEncoder.GetDistance() << endl;
}

void ClimbSubsystem::teleopOutput(void){
	
	
	if (currentSpeed > 0){
		climbMotor.Set(climbTopLimit.Get() ? 0 : currentSpeed);
	} else {
		climbMotor.Set(climbBottomLimit.Get() ? 0 : currentSpeed);
	}
	SmartDashboard::PutNumber("Climber Speed", climbMotor.Get());
		
	float tiltSpeed;
	
	if (isDeTilting)
		tiltSpeed = .5;
	else
		tiltSpeed = tilting ? -.5 : 0;
	
	if (tiltSpeed > 0){
		tiltMotor.Set(!tiltPosLimit.Get() ? 0 : tiltSpeed);
	} else {
		tiltMotor.Set(tiltNegLimit.Get() ? 0 : tiltSpeed);
	}
}
