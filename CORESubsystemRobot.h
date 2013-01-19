#include "WPILib.h"
#include "COREJoystick.h"
#include <string>
#include <vector>

#ifndef _CORESubsystemRobot_
#define _CORESubsystemRobot_
	

class CORESubsystem {
	
public:
					CORESubsystem(void);
	virtual 		~CORESubsystem(void){};	// class destructor defined to suppress compiler error
	virtual void	teleopInit(void) = 0;	
	virtual void	teleopInput(COREJoystick&) = 0;
	virtual void	teleopLogic(void) = 0;
	virtual void	teleopOutput(void) = 0;
	
	virtual std::string name(void) = 0;
};

class CORERobot {
	vector <CORESubsystem*> subsystems;
	
public:
	CORERobot(void);
	void add(CORESubsystem&);
	void teleopInit(void);
	void teleop(COREJoystick&);
	static void console( );
};

#endif
