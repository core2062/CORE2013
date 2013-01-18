#include "WPILib.h"
#include "CORESubsystemRobot.h"
#include <cmath>

#ifndef DRIVESUBSYSTEM_H
#define DRIVESUBSYSTEM_H

class LiftSubsystem : public CORESubsystem{
	
	bool isTilting;
	bool speedFull;
	bool speedHalf;
	float currentSpeed;
	Jaguar motorShooter;
	Jaguar motorTilter;
	
public:
	LiftSubsystem(void);
	
	std::string name(void){return "Lift";};

	void teleopInit(void);
	
	void teleopInput(COREJoystick& joystick);
	
	void teleopLogic(void);
	
	void teleopOutput(void);
	//Return values
	//0- Half speed
	//1- Normal Speed
	//2- Full Speed
	float getLiftSpeed(void);
};
#endif
