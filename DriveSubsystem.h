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
	
//	Gyro gyro;
	
	COREDrivePIDOut leftOut;
	COREDrivePIDOut rightOut;
	
	CORERateLimiter magLimiter;
	CORERateLimiter rotLimiter;
	
	SpeedPID PIDLeft;
	SpeedPID PIDRight;
		
	COREDrive m_drive;
	
	float mag;
	float rotate;
	float tank_left;
	float tank_right;
	float steer_x;
	float steer_y;
	
	bool quickturn;
	
//	SendableChooser controlSelect;
	SendableChooser algoSelect;
	
//	std::string control;
	std::string algo;
	
	bool autoRotateLeft;
	bool autoRotateRight;
	
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
	double m_dist;
	double m_start;
	DriveSubsystem* m_drive;
public:
	DriveAction(DriveSubsystem& drive, double mag, double dist){
		m_drive = &drive;
		m_mag = mag;
		m_dist = dist;
		m_start = m_drive->getDistance();
	}
	Action::ControlFlow call(void){
		double d = m_drive->getDistance() - m_start;
		cout << d <<endl;
		cout << m_dist << endl;
		bool done;
		if (m_mag > 0){
			done = d > m_dist;
		} else{
			done = d < m_dist;
		}
		if(!done){
			m_drive->drive(m_mag, 0);
			return CONTINUE;
		}else{
			cout << "pop!" <<endl;
			m_drive->drive(0,0);
			return END;
		}
	}
};

class RotateAction : public Action{
	double m_rot;
	DriveSubsystem* m_drive;
	Timer timer;
	double m_time;
	
public:
	RotateAction(DriveSubsystem& drive, double rot, double time):
		timer()
	{
		m_drive = &drive;
		m_rot = rot;
		m_time = time;
	}
	virtual ControlFlow call(void){
		if(timer.Get()==0){
				timer.Start();
		}
		if(timer.Get()<=m_time){
			m_drive->drive(0, m_rot);
			return CONTINUE;
		}else{
			m_drive->drive(0, 0);
			return END;
		}
	}
};

#endif
