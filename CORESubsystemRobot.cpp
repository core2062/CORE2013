#include "CORESubsystemRobot.h"

CORERobot::CORERobot(void):
	subsystems(){}

void CORERobot::add(CORESubsystem& sub){
	
	subsystems.push_back( &sub );
}

void CORERobot::teleopInit(void){
	cout << "teleop init" << endl;
	for(std::vector<CORESubsystem*>::iterator it = subsystems.begin(); it != subsystems.end(); ++it){
		cout << "teleop init " << (*it)->name() << endl;
		(*it)->teleopInit();
	}
}

void CORERobot::teleop(COREJoystick& joystick){
	cout << "teleop" << endl;
	
	std::vector<CORESubsystem*>::iterator it;
	
	for(it = subsystems.begin(); it != subsystems.end(); ++it){
		cout << "teleop input " << (*it)->name() << endl;
		(*it)->teleopInput(joystick);
	}

	for(it = subsystems.begin(); it != subsystems.end(); ++it){
		cout << "teleop logic " << (*it)->name() << endl;
		(*it)->teleopLogic();
	}

	for(it = subsystems.begin(); it != subsystems.end(); ++it){
		cout << "teleop output " << (*it)->name() << endl;
		(*it)->teleopOutput();
	}
}

CORESubsystem::CORESubsystem(void){}

std::string CORESubsystem::name(void){
	return "undefined name";
}

void CORESubsystem::teleopInit(void){
	printf("Unimplemented teleop_init\n");
}

void CORESubsystem::teleopInput(COREJoystick& joystick){
	printf("Unimplemented teleop_inputs\n");
}

void CORESubsystem::teleopLogic(void){
	printf("Unimplemented teleop_logic\n");
}

void CORESubsystem::teleopOutput(void){
	printf("Unimplemented teleop_outputs\n");
}
