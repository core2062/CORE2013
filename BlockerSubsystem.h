#include "WPILib.h"
#include "CORESubsystemRobot.h"
#include <string.h>

#ifndef BLOCKERSUBSYSTEM_H
#define BLOCKERSUBSYSTEM_H

class BlockerSubsystem : public CORESubsystem{
	Jaguar	winch;
	DigitalInput top;
	DigitalInput bottom;
	
	bool up;
	bool blockInUp;
	bool blockInDown;
	bool blockOut;
	
//	distance code from climb
	
	void SetPIDCommand(void);
	
public:
	static const int dist = 4*4;
	
	BlockerSubsystem(void);
	
	std::string name(void);
	
	void robotInit(void);

	
	/****	TELEOP		****/
	
	void teleopInit(void);
	
	void teleopInput(COREJoystick& joystick);
	
	void teleopLogic(void);
	
	void teleopOutput(void);
};
#endif
