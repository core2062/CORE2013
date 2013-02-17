#include "WPILib.h"
#include "CORESubsystemRobot.h"
#include <string.h>
#include "COREDrive.h"
#include "SpeedPID.h"

#ifndef DRIVESUBSYSTEM_H
#define DRIVESUBSYSTEM_H



class DriveSubsystem : public CORESubsystem{
	Jaguar FLDrive;
	Jaguar RLDrive;
	Jaguar FRDrive;
	Jaguar RRDrive;
	
	Encoder left;
	Encoder right;
	
	COREDrivePIDOut leftOut;
	COREDrivePIDOut rightOut;
	
	SpeedPID PIDLeft;
	SpeedPID PIDRight;
	
	COREDrive drive;
	
	float	mag;
	float	rotate;
	
	SendableChooser controlSelect;
	SendableChooser algoSelect;
	
	std::string control;
	std::string algo;
	
	void SetPIDCommand(void);
	
public:
	DriveSubsystem(void);
	
	std::string name(void);

	void teleopInit(void);
	
	void teleopInput(COREJoystick& joystick);
	
	void teleopLogic(void);
	
	void teleopOutput(void);
};
#endif
