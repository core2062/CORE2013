#include "CORESubsystemRobot.h"

CORERobot::CORERobot(void):
	subsystems(){}

void CORERobot::add(CORESubsystem& sub){
	
	subsystems.push_back( &sub );
}

void CORERobot::teleopInit(void){
	cout << "teleop init";
	for(std::vector<CORESubsystem*>::iterator i = subsystems.begin(); i != subsystems.end(); ++i){
		(*i)->teleopInit();
		cout << "teleop init " << (*(*i)).name();
	}
}

void CORERobot::teleop(COREJoystick& joystick){
	cout << "teleop";
	
	for(std::vector<CORESubsystem*>::iterator i = subsystems.begin(); i != subsystems.end(); ++i){
		(*i)->teleopInput(joystick);
		cout << "teleop input " << (*(*i)).name();
	}

	for(std::vector<CORESubsystem*>::iterator i = subsystems.begin(); i != subsystems.end(); ++i){
		(*i)->teleopLogic();
		cout << "teleop logic " << (*(*i)).name();
	}

	for(std::vector<CORESubsystem*>::iterator i = subsystems.begin(); i != subsystems.end(); ++i){
		(*i)->teleopOutput();
		cout << "teleop output " << (*(*i)).name();
	}
}
