#include "WPILib.h"
#include "CORESubsystemRobot.h"
#include <cmath>

#ifndef SHOOTERSUBSYSTEM_H
#define SHOOTERSUBSYSTEM_H

class ShooterSubsystem : public CORESubsystem{
	Victor shooterMotor;
	DigitalInput hopperSwitch;
	//Encoder shooterEncoder;
	
	float shooterValue;
	float shooterOutput;
	float shooterInc;
	float shooterDefault;
	
	bool pyramidSpeed;
	bool oldPyramidSpeed;
	bool shooterOn;
	bool up;
	bool oldUp;
	bool down;
	bool oldDown;
	bool shoot;
	
public:
	ShooterSubsystem(void);
	
	std::string name(void);

	void teleopInit(void);
	
	void teleopInput(COREJoystick& joystick);
	
	void teleopLogic(void);
	
	void teleopOutput(void);
};
#endif
