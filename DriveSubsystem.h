#include "WPILib.h"
#include "CORESubsystemRobot.h"
#include <cmath>

#ifndef DRIVESUBSYSTEM_H
#define DRIVESUBSYSTEM_H

class DriveSubsystem : public CORESubsystem{
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
};
#endif
