#include "CORESubsystemRobot.h"

CORESubsystem::CORESubsystem(void){
	
}

CORERobot::CORERobot(void){
	
}

void	CORERobot::add(CORESubsystem& sub){
	
	subsystems.push_back( &sub );
}

void	CORERobot::teleopInit(void){
	for(std::vector<CORESubsystem*>::iterator i = subsystems.begin(); i != subsystems.end(); ++i){
		(*i)->teleopInit();
	}
}
void	CORERobot::teleop(COREJoystick& joystick){
	
	for(std::vector<CORESubsystem*>::iterator i = subsystems.begin(); i != subsystems.end(); ++i){
		(*i)->teleopInput(joystick);
	}

	for(std::vector<CORESubsystem*>::iterator i = subsystems.begin(); i != subsystems.end(); ++i){
		(*i)->teleopLogic();
	}

	for(std::vector<CORESubsystem*>::iterator i = subsystems.begin(); i != subsystems.end(); ++i){
		(*i)->teleopOutput();
	}

	
}
