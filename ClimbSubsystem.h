#include "WPILib.h"
#include "CORESubsystemRobot.h"
#include <cmath>

#ifndef CLIMBSUBSYSTEM_H
#define CLIMBSUBSYSTEM_H

class Segment {
public:
	const float speed;
	const float pos;
	
	Segment(float speed, float pos):
	speed(speed),
	pos(pos)
	{}
};

class ClimbSubsystem : public CORESubsystem{
	Jaguar climbMotor;
	Jaguar tiltMotor;
	
	DigitalInput tiltPosLimit;
	DigitalInput tiltNegLimit;
	DigitalInput climbTopLimit;
	DigitalInput climbBottomLimit;
	
	Encoder	climbEncoder;
	
	bool tilting;
	bool isDeTilting;
	bool climbing;
	
	// Remove if wanted:
	bool reset;
	
	float currentSpeed;
	
	int stepCount;
	
public:
	ClimbSubsystem(void);
	
	std::string name(void){return "Climb";};

	void robotInit(void);

	void teleopInit(void);
	
	void teleopInput(COREJoystick& joystick);
	
	void teleopLogic(void);
	
	void teleopOutput(void);

};
#endif
