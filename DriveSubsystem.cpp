#include "CORESubsystemRobot.h"
#include "DriveSubsystem.h"
#include <string.h>
#include <cmath>
#include "private/trigP.h"

float deadband(float value, float range = .05);

DriveSubsystem::DriveSubsystem(void):
	FLDrive(CORERobot::DRIVE_LEFT_FRONT),
	RLDrive(CORERobot::DRIVE_LEFT_REAR),
	FRDrive(CORERobot::DRIVE_RIGHT_FRONT),
	RRDrive(CORERobot::DRIVE_RIGHT_REAR),
	
	left(CORERobot::DRIVE_LEFT_ENC_A, CORERobot::DRIVE_LEFT_ENC_B, true),
	right(CORERobot::DRIVE_RIGHT_ENC_A, CORERobot::DRIVE_RIGHT_ENC_B, true),
	
//	gyro(CORERobot::DRIVE_GYRO),

	leftOut(&FLDrive, &RLDrive),
	rightOut(&FRDrive, &RRDrive),

	magLimiter(.2),
	rotLimiter(.2),
	
	PIDLeft(0, 0.0, 0, 1, &left, &leftOut),
	PIDRight(0, 0.0, 0, 1, &right, &rightOut),

	m_drive( PIDLeft, PIDRight )
	
//	controlSelect(),
//	algoSelect()
{
	//drive.SetInvertedMotor(RobotDrive::kFrontLeftMotor,true);
	//drive.SetInvertedMotor(RobotDrive::kFrontRightMotor,true);
	m_drive.SetInvertedMotor(RobotDrive::kRearLeftMotor,true);
	m_drive.SetInvertedMotor(RobotDrive::kRearRightMotor,true);
	m_drive.SetSafetyEnabled(false);
	m_drive.SetMaxOutput( 1 );
	
	right.SetDistancePerPulse((1.0/360.0) * (6*3.141));
	left.SetDistancePerPulse((1.0/360.0) * (6*3.141));
	right.SetPIDSourceParameter(Encoder::kRate);
	left.SetPIDSourceParameter(Encoder::kRate);
	right.Start();
	left.Start();
		
//	controlSelect.AddObject("Tank", new std::string("tank"));
//	controlSelect.AddObject("Arcade", new std::string("arcade"));
//	controlSelect.AddDefault("Kaj", new std::string("kaj"));
	
//	algoSelect.AddObject("Classic", new std::string("classic"));
//	algoSelect.AddDefault("Ether", new std::string("ether"));
	
	autoRotateLeft = false;
	autoRotateRight = false;
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

void DriveSubsystem::robotInit(void){
	PIDLeft.SetSetpoint(0);
	PIDRight.SetSetpoint(0);
	PIDLeft.Enable();
	PIDRight.Enable();
//	SmartDashboard::PutNumber("gyro-gain", 7);
}

void DriveSubsystem::teleopInit(void){
//	m_drive.SetSafetyEnabled(true);
	m_drive.ArcadeDrive(0,0);
//	gyro.Reset();
//	gyro.SetSensitivity(SmartDashboard::GetNumber("gyro-gain")/1000.0);
	
//	SmartDashboard::PutNumber("Right P", PIDRight.GetP());
//	SmartDashboard::PutNumber("Right I", PIDRight.GetI());
//	SmartDashboard::PutNumber("Right D", PIDRight.GetD());
//	SmartDashboard::PutNumber("Right F", PIDRight.GetF());
//	SmartDashboard::PutNumber("R Setpoint", PIDRight.GetSetpoint());
//
//	SmartDashboard::PutNumber("Left P", PIDLeft.GetP());
//	SmartDashboard::PutNumber("Left I", PIDLeft.GetI());
//	SmartDashboard::PutNumber("Left D", PIDLeft.GetD());
//	SmartDashboard::PutNumber("Left F", PIDLeft.GetF());
//	SmartDashboard::PutNumber("L Setpoint", PIDLeft.GetSetpoint());
	
//	SmartDashboard::PutData("Control Selecter", &controlSelect);
//	SmartDashboard::PutData("Algo Selecter", &algoSelect);
	
	SmartDashboard::PutNumber("Ether A", .5);
	SmartDashboard::PutNumber("Ether B", .5);
	
	SmartDashboard::PutNumber("Left", 0);
	SmartDashboard::PutNumber("Right", 0);
	
//	SmartDashboard::PutBoolean("Cubed inputs", false);
	
//	SmartDashboard::PutNumber("Gyro Angle Raw", 0);
//	SmartDashboard::PutNumber("Gyro Angle Rounded", 0);
	
	SmartDashboard::PutNumber("Pyramid Speed", 0.707);

}

void DriveSubsystem::teleopInput(COREJoystick& joystick){
//	control = *((std::string *) controlSelect.GetSelected());
//	if (control == "arcade"){
//		mag = joystick.driveClassicMag();
//		rotate = joystick.driveClassicRot();
//	}
//	if (control == "kaj"){
		mag= joystick.driveKajMag();
		rotate = joystick.driveKajRot();
//	}else{
//		cout << "  !!Error in controlSelect!!  " << endl;
//	}
//	algo = *((std::string *) algoSelect.GetSelected());
//	autoRotateLeft = joystick.autoRotLeft();
//	autoRotateRight = joystick.autoRotRight();
}

void DriveSubsystem::teleopLogic(void){
//	float gyroAngle = gyro.GetAngle();
//	float gyroAngleRounded = drem( gyroAngle, 360 );
	
	mag = deadband(mag);
	rotate = deadband(rotate);

//	if (mag == 0 and rotate == 0){
//		if (autoRotateLeft and (gyro.GetAngle() < 41.5)){
//			rotate = .5;
//		}
//		if (autoRotateLeft and (gyro.GetAngle() > 42.5)){
//			rotate = -.5;
//		}
//		if (autoRotateRight and (gyro.GetAngle() < -41.5)){
//			rotate = -.5;
//		}
//		if (autoRotateRight and (gyro.GetAngle() > -42.5)){
//			rotate = .5;
//		}
//	}
	SmartDashboard::PutNumber("Mag", mag); SmartDashboard::PutNumber("Rot", rotate);
	
//	SmartDashboard::PutNumber("Gyro Angle Raw", gyroAngle);
//	SmartDashboard::PutNumber("Gyro Angle Rounded", gyroAngleRounded);
}
float deadband(float value, float range){
	if(std::abs(value) < range){
		return 0;
	}
	return value;
}

void DriveSubsystem::teleopOutput(void){
	
	SmartDashboard::PutNumber("Left", left.GetRate());
	SmartDashboard::PutNumber("Right", right.GetRate());
	
//	mag = magLimiter.limit(mag);
//	
//	if(algo == "classic"){
//		m_drive.ArcadeDrive(mag, rotate);
//	} else if (algo == "ether"){
		double a = SmartDashboard::GetNumber("Ether A");
		double b = SmartDashboard::GetNumber("Ether B");
		m_drive.EtherArcade(mag, -rotate, a, b);
//	}

	
	if (CORERobot::isDevMode()){
//		SetPIDCommand();
		SmartDashboard::PutNumber("DriveDistance", getDistance());
	}

}

/****	AUTONOMOUS		****/

void DriveSubsystem::drive(double mag, double rot){
	m_drive.ArcadeDrive(-mag, rot);
}

void DriveSubsystem::stop(void){
	drive(0,0);
}

double DriveSubsystem::getDistance(void){
	return (right.GetDistance() + left.GetDistance()) / 2.0;
}

void DriveSubsystem::driveTest(void){
//	drive.SetExpiration(100000000);
	m_drive.Drive(1,0);
	
//	SmartDashboard::PutNumber("Left", left.GetRate());
//	SmartDashboard::PutNumber("Right", right.GetRate());
//	drive.SetSafetyEnabled(false);
}
