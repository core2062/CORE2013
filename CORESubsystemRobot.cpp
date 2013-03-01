#include "CORESubsystemRobot.h"

bool CORERobot::developerMode = false;

CORERobot::CORERobot(void):
	subsystems(),
	timer()
{
	timer.Start();
}

void CORERobot::add(CORESubsystem& sub){
	subsystems.push_back( &sub );
}


void CORERobot::robotInit(void){
	cout << "robot init" << endl;
	for(std::vector<CORESubsystem*>::iterator it = subsystems.begin(); it != subsystems.end(); ++it){
		cout << "robot init " << (*it)->name() << endl;
		(*it)->robotInit();
	}
}

void CORERobot::teleopInit(void){
	cout << "teleop init" << endl;
	for(std::vector<CORESubsystem*>::iterator it = subsystems.begin(); it != subsystems.end(); ++it){
		cout << "teleop init " << (*it)->name() << endl;
		(*it)->teleopInit();
	}
}

void CORERobot::teleop(COREJoystick& joystick){
	// cout << "teleop" << endl;
	
	std::vector<CORESubsystem*>::iterator it;
	
	for(it = subsystems.begin(); it != subsystems.end(); ++it){
//		cout << "teleop input " << (*it)->name() << endl;
//		timer.Reset();
		(*it)->teleopInput(joystick);
//		cout<< "    " << timer.Get()<<endl;
	}

	for(it = subsystems.begin(); it != subsystems.end(); ++it){
//		cout << "teleop logic " << (*it)->name() << endl;
//		timer.Reset();
		(*it)->teleopLogic();
//		cout<< "    " << timer.Get()<<endl;
	}

	for(it = subsystems.begin(); it != subsystems.end(); ++it){
//		cout << "teleop output " << (*it)->name() << endl;
//		timer.Reset();
		(*it)->teleopOutput();
//		cout<< "    " << timer.Get()<<endl;
	}
}

CORESubsystem::CORESubsystem(void){}

std::string CORESubsystem::name(void){
	return "undefined name";
}
void CORESubsystem::robotInit(void){
	printf("Unimplemented robot_init\n");
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

bool CORERobot::isDevMode(){
	return(developerMode);
}

void CORERobot::setDevMode(bool mode){
	developerMode = mode;
}
