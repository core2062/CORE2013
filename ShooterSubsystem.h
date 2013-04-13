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
	bool		oldState;
	
public:
	SensorEdge();
	bool Get();
	bool Rise();
	
	float GetVoltage();
};


class ShooterSubsystem : public CORESubsystem{
	Jaguar 			shooterMotor;
	Jaguar 			pusher;
	Timer			pusherTimer;
	PIDCounter		shooterOptEncoder;
	PIDController 	pid;
	SensorEdge		pusherSensor;

	static const float shooterInc = 1;		 // value is in rps
	static const float shooterDefault = 58;
	
	float shooterValue;
	float shooterOutput;
	
	bool pyramidSpeed;
	bool shooterOn;
	bool shooterRunning;
	bool up;
	bool down;
	bool shooterSpeedOverride;
	bool shooterAtSpeed;
	
	int feed;
	bool isFeeding;
	int pusherOutput;
	
	
public:
	static const float pushTime = .42;	 // Pusher activation timing
//	 Practice robot is more like .46 for some reason
	
	ShooterSubsystem(void);
	
	std::string name(void);

	void robotInit(void);

	void teleopInit(void);
	
	void teleopInput(COREJoystick& joystick);
	
	void teleopLogic(void);
	
	void teleopOutput(void);
	
	void shoot(float shooterOutput);
	
	void push(float pusherOutput);
	
	bool getUpToSpeed(void);
};

class ShootAction : public Action{
	ShooterSubsystem* m_shooter;
	Timer pusher_timer;
	Timer recovery_timer;
	bool started;
	int discs_shot;
	int n_discs;
	static const float recovery_time = 1;
public:
	ShootAction(ShooterSubsystem& shoot, int discs):
		pusher_timer(),
		recovery_timer()
	{
		m_shooter = &shoot;
		n_discs = discs;
		discs_shot = 0;
		started = false;
	}
	ControlFlow call(void){
		cout << "Call called" << endl;
		if (discs_shot < n_discs){ //if we didn't shoot all the discs we wanted to
			m_shooter->shoot(1);
			//m_shooter->getUpToSpeed() or 
			cout << "recovery: " << recovery_timer.Get()<<endl;
			if ((recovery_timer.Get() > recovery_time)){		//ready is shooter up-to-speed or recovery time > time to recover
				recovery_timer.Stop();
				cout << "pusher: " << pusher_timer.Get() << endl;
				if (pusher_timer.Get()==0){
					m_shooter->push(1);
					pusher_timer.Start();
				}else if (pusher_timer.Get() >= ShooterSubsystem::pushTime){
					++discs_shot;
					m_shooter->push(0);
					pusher_timer.Stop();
					pusher_timer.Reset();
					recovery_timer.Reset();
					recovery_timer.Start();
				}else{
					m_shooter->push(1);
				}
			} else if (recovery_timer.Get()==0){
				recovery_timer.Start();
			}
			return CONTINUE;
		}else{
			m_shooter->shoot(0);
			return END;
		}
	}
};
#endif
