#include "WPILib.h"
#include "CORESubsystemRobot.h"
#include <cmath>
#include "COREAuto.h"

#ifndef SHOOTERSUBSYSTEM_H
#define SHOOTERSUBSYSTEM_H
using namespace CORE;

class PIDCounter : public Counter, public PIDSource{
	INT32 prevCounterVal;
	double prevPeriod;

public:
	PIDCounter(UINT32 channel);
	double	PIDGet ();
};

class SensorEdge {
	AnalogChannel	puckPhotoEye;
	bool		oldRState;
	bool		oldFState;
	
public:
	SensorEdge();
	bool Get();
	bool Rise();
	bool Fall();
	float GetVoltage();
};


class ShooterSubsystem : public CORESubsystem{
	Jaguar 			shooterMotor;
	Jaguar 			pusher;
	Timer			pusherTimer;
	Timer			jamTimer;
	PIDCounter		shooterOptEncoder;
	PIDController 	pid;
	SensorEdge		pusherSensor;
	
	static const float shooterInc = 1;		 // value is in rps
	static const float shooterDefault = 64;
	
	float shooterValue;
	float shooterOutput;
	
	bool pyramidSpeed;
	bool shooterOn;
	bool shooterRunning;
	bool up;
	bool down;
	bool shooterSpeedOverride;
	bool isJammed;
	bool pushMan;
	
	int feed;
	bool isFeeding;
	float pusherOutput;
	
	
public:
	static const float pushTime = .42;	 // DEPRECATED
	static const float jamThresh = 1; // seconds
	
	ShooterSubsystem(void);
	
	std::string name(void);

	void robotInit(void);

	void teleopInit(void);
	
	void teleopInput(COREJoystick& joystick);
	
	void teleopLogic(void);
	
	void teleopOutput(void);
	
	void shoot(float shooterOutput);
	
	void push(float pusherOutput);
	
	bool isAtSpeed(float val);
	bool isAtSpeed(void);
	
	bool sensorEdge(float dir);
};

class ShootAction : public Action{
	ShooterSubsystem* m_shooter;
	Timer pusher_timer;
	Timer recovery_timer;
	bool started;
	int discs_shot;
	int n_discs;
	bool pushing;
	static const float recovery_time = .25;
public:
	ShootAction(ShooterSubsystem& shoot, int discs):
		pusher_timer(),
		recovery_timer()
	{
		m_shooter = &shoot;
		n_discs = discs+1;
		discs_shot = 0;
		started = false;
		pushing = false;
	}
	ControlFlow call(void){
//		cout << "Call called" << endl;
		if (not started){
			started = true;
			recovery_timer.Start();
		}
		if (discs_shot < n_discs){ //if we didn't shoot all the discs we wanted to
			bool s = m_shooter->sensorEdge(1);
			cout<< "d: " << discs_shot <<
				   " s: " << s << " p: "<<pushing << " a: "<<m_shooter->isAtSpeed() <<endl;
			m_shooter->shoot(1);
			if (s and pushing){
				pushing = false;
				recovery_timer.Reset();
				recovery_timer.Start();
				discs_shot++;
			} else {
				if((not pushing) and m_shooter->isAtSpeed() and recovery_timer.Get()>recovery_time){
					recovery_timer.Stop();
					pushing = true;
				}
			}
			m_shooter->push(pushing);
		}else{
			m_shooter->shoot(0);
			return END;
		}
		return CONTINUE;
	}
};
#endif
