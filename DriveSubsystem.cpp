#include "CORESubsystemRobot.h"
#include "DriveSubsystem.h"
#include <string.h>
#include <cmath>

float deadband(float value, float range = .1);

DriveSubsystem::DriveSubsystem(void):
	FLDrive(3),
	RLDrive(4),
	FRDrive(5),
	RRDrive(6),
	
	drive(FLDrive,RLDrive,FRDrive,RRDrive),

	right(2, 1),
	left(4, 3),
	
	
	// TODO: implement pid control on drive
//	PIDRight(0.09, 0 ,0, 0.021, &shooterOptEncoder, &shooterMotor),
//	PIDLeft(0.09, 0 ,0, 0.021, &shooterOptEncoder, &shooterMotor),
	
	controlSelect(),
	algoSelect()
{
	drive.SetInvertedMotor(RobotDrive::kFrontLeftMotor,true);
	drive.SetInvertedMotor(RobotDrive::kFrontRightMotor,true);
	drive.SetInvertedMotor(RobotDrive::kRearLeftMotor,true);
	drive.SetInvertedMotor(RobotDrive::kRearRightMotor,true);
	
	right.SetDistancePerPulse(1.0/360.0);
	left.SetDistancePerPulse(1.0/360.0);
	
	controlSelect.AddDefault("Tank", new std::string("tank"));
	controlSelect.AddObject("Arcade", new std::string("arcade"));
	controlSelect.AddObject("Kaj", new std::string("kaj"));
	
	algoSelect.AddDefault("Classic", new std::string("classic"));
	algoSelect.AddObject("Ether", new std::string("ether"));
}
std::string DriveSubsystem::name(void){
	return "Drive";
}

void DriveSubsystem::teleopInit(void){
	right.Start();
	left.Start();
	SmartDashboard::PutData("Control Selecter", &controlSelect);
	SmartDashboard::PutData("Algo Selecter", &algoSelect);
	
	SmartDashboard::PutNumber("Ether A", .5);
	SmartDashboard::PutNumber("Ether B", .5);
	
	SmartDashboard::PutNumber("Right", 0);
	SmartDashboard::PutNumber("Right", 0);
}

void DriveSubsystem::teleopInput(COREJoystick& joystick){
	control = *((std::string *) controlSelect.GetSelected());
	if(control == "tank"){
		tankRight = joystick.driveRight();
		tankLeft = joystick.driveLeft();
	}else if (control == "arcade"){
		classicMag = joystick.driveClassicMag();
		classicRot = joystick.driveClassicRot();
	}else if (control == "kaj"){
		kajMag = joystick.driveKajMag();
		kajRot = joystick.driveKajRot();
	}else{
		cout << "  !!Error in controlSelect!!  " << endl;
	}
	algo = *((std::string *) algoSelect.GetSelected());
}

void DriveSubsystem::teleopLogic(void){	
	if(control == "tank"){
		tankRight = deadband(tankRight);
		tankLeft = deadband(tankLeft);
	}
	else if (control == "arcade"){
		classicMag = deadband(classicMag);
		classicRot = deadband(classicRot);
	}
	else if (control == "kaj"){
		kajMag = deadband(kajMag);
		kajRot = deadband(kajRot);
	}
}

void DriveSubsystem::teleopOutput(void){
	
	SmartDashboard::PutNumber("Left", left.GetRate());
	SmartDashboard::PutNumber("Right", right.GetRate());
	
	if(control == "tank"){
		drive.TankDrive(tankLeft, tankRight); return;
	}else{
		double mag, rotate;
		if(control == "arcade"){
			mag = classicMag;
			rotate = classicRot;
		}else{
			mag = kajMag;
			rotate = kajRot;
		}
		
		if(algo == "classic"){
			drive.ArcadeDrive(mag, rotate);
		} else if (algo == "ether"){
			double a = SmartDashboard::GetNumber("Ether A");
			double b = SmartDashboard::GetNumber("Ether B");
			drive.EtherArcade(mag, -rotate, a, b);
		}
	}
}

float deadband(float value, float range){
	if(std::abs(value) < range){
		return 0;
	}
	return value;
}
