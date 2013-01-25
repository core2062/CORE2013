#include "WPILib.h"
#include "CORESubsystemRobot.h"
#include <cmath>

#ifndef DRIVESUBSYSTEM_H
#define DRIVESUBSYSTEM_H

class DriveSubsystem : public CORESubsystem{
	Jaguar FLDrive;
	Jaguar RLDrive;
	Jaguar FRDrive;
	Jaguar RRDrive;
	
	RobotDrive drive;
	
	float	driveRight;
	float	driveLeft;
	
	float	driveMag;
	float	driveRotate;
	bool	driveArcade;
	
public:
	DriveSubsystem(void);
	
	std::string name(void);

	void teleopInit(void);
	
	void teleopInput(COREJoystick& joystick);
	
	void teleopLogic(void);
	
	void teleopOutput(void);
	

	Jaguar* getFLDrive(void);
	Jaguar* getRLDrive(void);
	Jaguar* getFRDrive(void);
	Jaguar* getRRDrive(void);
};
#endif
