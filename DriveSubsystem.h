#include "WPILib.h"
#include "CORESubsystemRobot.h"
#include <string.h>
#include "COREDrive.h"
#include "SpeedPID.h"
#include "COREAuto.h"

#ifndef DRIVESUBSYSTEM_H
#define DRIVESUBSYSTEM_H
using namespace CORE;

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
	
	COREDrive m_drive;
	
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
	
	void robotInit(void);

	
	/****	TELEOP		****/
	
	void teleopInit(void);
	
	void teleopInput(COREJoystick& joystick);
	
	void teleopLogic(void);
	
	void teleopOutput(void);
	
	
	/****	AUTONOMOUS	****/
	
	void drive(double mag, double rot=0.0);
	
	void stop(void);
	
	double getDistance(void);

	
	/****	TEST		****/
	
	void driveTest(void);
};

class DriveAction : public Action{
	double m_mag;
	double m_rot;
	DriveSubsystem* m_drive;
public:
	DriveAction(DriveSubsystem& drive, double mag, double rot){
		m_drive = &drive;
		m_mag = mag;
		m_rot = rot;
	}
	ControlFlow operator()(void){
		m_drive->drive(m_mag, m_rot);
		return CONTINUE;
	}
};

#endif
