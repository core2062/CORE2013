#include "CORESubsystemRobot.h"
#include "BlockerSubsystem.h"
#include <string.h>

BlockerSubsystem::BlockerSubsystem(void):
winch(CORERobot::BLOCKER_WINCH),
top(CORERobot::BLOCKER_LIMIT_TOP),
bottom(CORERobot::BLOCKER_LIMIT_BOTTOM)
{
	up = false;
}

std::string BlockerSubsystem::name(void){
	return "Blocker";
}

void BlockerSubsystem::robotInit(void){
	SmartDashboard::PutNumber("blocker-mult", .9);
	SmartDashboard::PutBoolean("top", false);
	SmartDashboard::PutBoolean("bottom", false);
}

void BlockerSubsystem::teleopInit(void){
}

void BlockerSubsystem::teleopInput(COREJoystick& joystick){
	blockInUp = joystick.block();
	blockInDown = joystick.blockDown();
}

void BlockerSubsystem::teleopLogic(void){
//	if (blockIn){
//		up = !up;
//	}
//	if (up){
//		if(counter.Get() < dist){
//			blockOut = 1;
//		}
//	} else{
//		if(counter.Get() > 0){
//			blockOut = -1;
//		}
//	}

	blockOut = blockInDown ? -1 : blockInUp ? 1 : 0;

}

void BlockerSubsystem::teleopOutput(void){
	SmartDashboard::PutBoolean("top", top.Get());
	SmartDashboard::PutBoolean("bottom", bottom.Get());

	blockOut *= SmartDashboard::GetNumber("blocker-mult");
	cout << bottom.Get() << top.Get() <<endl;
	if (bottom.Get() and blockOut < 0){
		blockOut = 0;
	} else if (top.Get() and blockOut > 0){
		blockOut = 0;
	}
	winch.Set(blockOut);
}
