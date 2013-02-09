#include "CORESubsystemRobot.h"
#include "DriveSubsystem.h"
#include <string.h>
#include <cmath>

float deadband(float value, float range = .1);

DriveSubsystem::DriveSubsystem(void):
	FLDrive(CORERobot::DRIVE_LEFT_FRONT),
	RLDrive(CORERobot::DRIVE_LEFT_REAR),
	FRDrive(CORERobot::DRIVE_RIGHT_FRONT),
	RRDrive(CORERobot::DRIVE_RIGHT_REAR),
	
	left(CORERobot::DRIVE_LEFT_ENC_A, CORERobot::DRIVE_LEFT_ENC_B, false),
	right(CORERobot::DRIVE_RIGHT_ENC_A, CORERobot::DRIVE_RIGHT_ENC_B, true),

	leftOut(&FLDrive, &RLDrive),
	rightOut(&FRDrive, &RRDrive),
	
	PIDLeft(0.01, 0, 0, 1.0, &left, &leftOut),
	PIDRight(0.01, 0, 0, 1.0, &right, &rightOut),
	
	drive(FLDrive, RLDrive, FRDrive, RRDrive, &PIDLeft, &PIDRight),
	
	controlSelect(),
	algoSelect()
{
	drive.SetInvertedMotor(RobotDrive::kFrontLeftMotor,true);
	drive.SetInvertedMotor(RobotDrive::kFrontRightMotor,true);
	drive.SetInvertedMotor(RobotDrive::kRearLeftMotor,true);
	drive.SetInvertedMotor(RobotDrive::kRearRightMotor,true);
	
	right.SetDistancePerPulse(1.0/360.0);
	left.SetDistancePerPulse(1.0/360.0);
	right.SetPIDSourceParameter(Encoder::kRate);
	left.SetPIDSourceParameter(Encoder::kRate);
	right.Start();
	left.Start();
	
	controlSelect.AddDefault("Tank", new std::string("tank"));
	controlSelect.AddObject("Arcade", new std::string("arcade"));
	controlSelect.AddObject("Kaj", new std::string("kaj"));
	
	algoSelect.AddDefault("Classic", new std::string("classic"));
	algoSelect.AddObject("Ether", new std::string("ether"));
}
std::string DriveSubsystem::name(void){
	return "Drive";
}

void DriveSubsystem::SetPIDCommand(void) {
	double pLeft = SmartDashboard::GetNumber("Left P");
	double iLeft = SmartDashboard::GetNumber("Left I");
	double dLeft = SmartDashboard::GetNumber("Left D");
	double fLeft = SmartDashboard::GetNumber("Left F");
	
	double pRight = SmartDashboard::GetNumber("Right P");
	double iRight = SmartDashboard::GetNumber("Right I");
	double dRight = SmartDashboard::GetNumber("Right D");
	double fRight = SmartDashboard::GetNumber("Right F");

	PIDLeft.SetPID(pLeft,iLeft,dLeft,fLeft);
	PIDRight.SetPID(pRight,iRight,dRight,fRight);
	
	SmartDashboard::PutNumber("R Setpoint", PIDRight.GetSetpoint());
	SmartDashboard::PutNumber("L Setpoint", PIDLeft.GetSetpoint());
	return;
}

void DriveSubsystem::teleopInit(void){

	SmartDashboard::PutNumber("Right P", PIDRight.GetP());
	SmartDashboard::PutNumber("Right I", PIDRight.GetI());
	SmartDashboard::PutNumber("Right D", PIDRight.GetD());
	SmartDashboard::PutNumber("Right F", PIDRight.GetF());
	SmartDashboard::PutNumber("R Setpoint", PIDRight.GetSetpoint());

	SmartDashboard::PutNumber("Left P", PIDLeft.GetP());
	SmartDashboard::PutNumber("Left I", PIDLeft.GetI());
	SmartDashboard::PutNumber("Left D", PIDLeft.GetD());
	SmartDashboard::PutNumber("Left F", PIDLeft.GetF());
	SmartDashboard::PutNumber("L Setpoint", PIDLeft.GetSetpoint());
	
	SmartDashboard::PutData("Control Selecter", &controlSelect);
	SmartDashboard::PutData("Algo Selecter", &algoSelect);
	
	SmartDashboard::PutNumber("Ether A", .5);
	SmartDashboard::PutNumber("Ether B", .5);
	
	SmartDashboard::PutNumber("Left", 0);
	SmartDashboard::PutNumber("Right", 0);
	PIDLeft.Enable();
	PIDRight.Enable();
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
		drive.TankDrive(tankLeft, tankRight); return; // TODO: Add closed loop
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
	

	SetPIDCommand();

}

float deadband(float value, float range){
	if(std::abs(value) < range){
		return 0;
	}
	return value;
}
