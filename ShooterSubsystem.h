#include "WPILib.h"
#include "CORESubsystemRobot.h"
#include <cmath>

#ifndef SHOOTERSUBSYSTEM_H
#define SHOOTERSUBSYSTEM_H

class PIDCounter : public Counter, public PIDSource{
public:
	PIDCounter(UINT32 channel);
	double	PIDGet ();
};

class ShooterSubsystem : public CORESubsystem{
	Jaguar 			shooterMotor;
	DigitalInput 	hopperSwitch;
	Relay 			feeder;
	Timer			feederTimer;
//	PIDCounter		shooterOptEncoder;
	Encoder			shooter360Encoder;
	
	PIDController 	pid;

	static const float shooterInc = 0.05;
	static const float shooterDefault = .5;
	static const float feederTime = .5;  		// energize pusher fore 5 seconds 
	
	float shooterValue;
	float shooterOutput;
	
	bool pyramidSpeed;
	bool shooterOn;
	bool shooterRunning;
	bool up;
	bool down;
	bool feed;
	bool feedingDisk;
	
	int n;
	
public:
	ShooterSubsystem(void);
	
	std::string name(void);

	void teleopInit(void);
	
	void teleopInput(COREJoystick& joystick);
	
	void teleopLogic(void);
	
	void teleopOutput(void);
};
#endif
