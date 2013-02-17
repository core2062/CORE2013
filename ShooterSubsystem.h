#include "WPILib.h"
#include "CORESubsystemRobot.h"
#include <cmath>

#ifndef SHOOTERSUBSYSTEM_H
#define SHOOTERSUBSYSTEM_H

class PIDCounter : public Counter, public PIDSource{
	INT32 prevCounterVal;
	double prevPeriod;

public:
	PIDCounter(UINT32 channel);
	double	PIDGet ();
};

class ShooterSubsystem : public CORESubsystem{
	Jaguar 			shooterMotor;
	Victor 			pusher;
	Timer			pusherTimer;
	PIDCounter		shooterOptEncoder;
	PIDController 	pid;

	static const float shooterInc = 1;		 // value is in rps
	static const float shooterDefault = 45;
	static const float pushTime = 1 / 2.0;	 // Pusher activation timing 
	
	float shooterValue;
	float shooterOutput;
	
	bool pyramidSpeed;
	bool shooterOn;
	bool shooterRunning;
	bool up;
	bool down;
	bool feed;
	bool feedingDisk;
	bool pusherOutput;
	bool shooterSpeedOverride;
	
public:
	ShooterSubsystem(void);
	
	std::string name(void);

	void teleopInit(void);
	
	void teleopInput(COREJoystick& joystick);
	
	void teleopLogic(void);
	
	void teleopOutput(void);
};
#endif
