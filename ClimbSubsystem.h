#include "WPILib.h"
#include "CORESubsystemRobot.h"
#include <cmath>

#ifndef CLIMBSUBSYSTEM_H
#define CLIMBSUBSYSTEM_H

class Segment {
public:
	const float pos;
	const float speed;
	
	Segment(float pos, float speed):
	pos(pos),
	speed(speed)
	{}
};

class ClimbSubsystem : public CORESubsystem{
	Jaguar climbMotor;
	Jaguar tiltMotor;
	
	DigitalInput tiltTopLimit;
	DigitalInput tiltBottomLimit;
	DigitalInput climbTopLimit;
	DigitalInput climbBottomLimit;
	
	Encoder	climbEncoder;
	
	bool isTilting;
	bool isDeTilting;
	bool speedFull;
	bool speedHalf;
	float currentSpeed;
	
	
public:
	ClimbSubsystem(void);
	
	std::string name(void){return "Climb";};

	void teleopInit(void);
	
	void teleopInput(COREJoystick& joystick);
	
	void teleopLogic(void);
	
	void teleopOutput(void);
	//Return values
	//0- Half speed
	//1- Normal Speed
	//2- Full Speed
	float getClimbSpeed(void);
};
#endif
