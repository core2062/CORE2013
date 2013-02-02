#include "WPILib.h"
#include "CORESubsystemRobot.h"
#include <string.h>
#include "COREDrive.h"

#ifndef DRIVESUBSYSTEM_H
#define DRIVESUBSYSTEM_H



class DriveSubsystem : public CORESubsystem{
	Jaguar FLDrive;
	Jaguar RLDrive;
	Jaguar FRDrive;
	Jaguar RRDrive;
	
	COREDrive drive;
	
	float	tankRight;
	float	tankLeft;
	
	float	classicMag;
	float	classicRot;
	
	float 	kajMag;
	float	kajRot;
	
	SendableChooser controlSelect;
	SendableChooser algoSelect;
	
	std::string control;
	std::string algo;
	
public:
	DriveSubsystem(void);
	
	std::string name(void);

	void teleopInit(void);
	
	void teleopInput(COREJoystick& joystick);
	
	void teleopLogic(void);
	
	void teleopOutput(void);
};
#endif
