#include "CORERobot.h"

CORERobot::CORERobot():
	subsystems(){}

void CORERobot::add(CORESubsystem& subsystem){
	subsystems.push_back(subsystem);
}

std::vector<CORESubsystem>& CORERobot::get_subsystems(void){
	return subsystems;
}

void CORERobot::teleop_init(void){
	for(std::vector<CORESubsystem>::iterator it = subsystems.begin(); it != subsystems.end(); ++it){
		it->teleop_init();
		cout << "tele init " << it->name;
	}
}

void CORERobot::teleop(COREJoystick& joystick){
	for (std::vector<CORESubsystem>::iterator it = subsystems.begin(); it != subsystems.end(); ++it){
		it->teleop_joystick(joystick);
		cout << "tele inputs " << it->name;
	}
	for (std::vector<CORESubsystem>::iterator it = subsystems.begin(); it != subsystems.end(); ++it){
		it->teleop_main();
		cout << "tele logic " << it->name;
	}
	for (std::vector<CORESubsystem>::iterator it = subsystems.begin(); it != subsystems.end(); ++it){
		it->teleop_motors();
		cout << "tele outputs " << it->name;
	}
}
