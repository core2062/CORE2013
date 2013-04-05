#include "WPILib.h"

#include "CORESubsystemRobot.h"
#include "COREJoystick.h"
#include "Subsystems.h"
#include <string>
#include "COREAuto.h"

#include "InsightLT/InsightLT.h"
using namespace CORE;
class CORE2013 : public SimpleRobot
{
	AutoSequencer autoSeq;
	
	CORERobot robot;
	COREJoystick joystick;
	
	DriveSubsystem drive;
	ShooterSubsystem shooter;
//	ClimbSubsystem climb;
	
	insight::InsightLT display;
	insight::DecimalData disp_userInfo;
	insight::DecimalData disp_batteryVoltage;
	
	Timer insightTime;
	
	SendableChooser autoMode;
	std::string autonomousMode;

public:
	
	CORE2013(void):
		autoSeq(),
		
		robot(),
		joystick(),
		
		drive(),
		shooter(),
//		climb(),
		
		display(insight::TWO_ONE_LINE_ZONES),
		
		insightTime()
	{
		robot.add(drive);
		robot.add(shooter);
//		robot.add(climb);
		insightTime.Start();
		
		
	}

	void RobotInit(void){
			robot.robotInit();
			SmartDashboard::PutNumber("drive-timing", 30);
			SmartDashboard::PutNumber("rotate-timing", 1.22);
			SmartDashboard::PutBoolean("Dev on", CORERobot::isDevMode());
			
			autoMode.AddObject("Do nothing", new std::string("do nothing"));
			autoMode.AddDefault("Shooter only", new std::string("shooter only"));
			autoMode.AddObject("Left of pramid", new std::string("left of pyramid"));
			autoMode.AddObject("Right of pyramid", new std::string("right of pyramid"));
			
//			autoMode.AddObject("Shoot only", new std::string("shoot only"));
//			autoMode.AddObject("Drive only", new std::string("drive only"));
//			autoMode.AddObject("Rotate only", new std::string("rotate only"));
			SmartDashboard::PutData("Autonomous mode", &autoMode);
		}

	void Autonomous(void){
		Watchdog &wd = GetWatchdog();
		wd.SetEnabled(false);
		wd.SetExpiration(.5);
		std::string* mode ((std::string *) autoMode.GetSelected());
		
		/* Shooter only actions*/
		ShootAction shoot_only (shooter, 6);
		
		/* Left of pyramid actions*/
		DriveAction drive_LOP1 (drive, .5, SmartDashboard::GetNumber("drive-timing"));
		RotateAction rotate_LOP1 (drive, .5, SmartDashboard::GetNumber("rotate-timing"));
		ShootAction shoot_LOP1 (shooter, 4);
		
		/* Right of pyramid actions*/
		DriveAction drive_ROP1 (drive, .5, SmartDashboard::GetNumber("drive-timing"));
		RotateAction rotate_ROP1 (drive, -.5, SmartDashboard::GetNumber("rotate-timing"));
		ShootAction shoot_ROP1 (shooter, 4);
		
		
		
		if(*mode == "shooter only"){
			autoSeq.add_action(shoot_only);
		}
		
		if(*mode == "left of pyramid"){
			autoSeq.add_action(drive_LOP1);
			autoSeq.add_action(rotate_LOP1);
			autoSeq.add_action(shoot_LOP1);
		}
		if(*mode == "right of pyramid"){
			autoSeq.add_action(drive_ROP1);
			autoSeq.add_action(rotate_ROP1);
			autoSeq.add_action(shoot_ROP1);
		}
		if(*mode == "do nothing"){
//			do nothing :D
		}
		
		while (IsAutonomous() and !IsDisabled()){
			wd.Feed();
			autoSeq.iter();

//			CORERobot::setDevMode(SmartDashboard::GetBoolean("Dev on"));
			
			Wait(0.05);				// wait for a motor update time
		}
	}

	void Disabled(void){
		cout << "Disabled" << endl;

		disp_batteryVoltage.setData((DriverStation::GetInstance())->GetBatteryVoltage());
		disp_batteryVoltage.setHeader("Batt:");
		disp_userInfo.setHeader("Match Time:");
		display.registerData(disp_userInfo, 1);
		display.registerData(disp_batteryVoltage, 2);
		display.startDisplay();
		
		while (IsDisabled()){
			disp_batteryVoltage.setData((DriverStation::GetInstance())->GetBatteryVoltage());
			disp_userInfo.setData(insightTime.Get());
			Wait(.05);
		}
	}

	void OperatorControl(void){
		Watchdog &wd = GetWatchdog();
		wd.SetEnabled(true);
		wd.SetExpiration(.5);
		
		robot.teleopInit();
		
		Timer teleop;
		teleop.Start();
		
		while (IsOperatorControl() and !IsDisabled()){
			teleop.Reset();
			wd.Feed();
				
			robot.teleop(joystick);

			CORERobot::setDevMode(SmartDashboard::GetBoolean("Dev on"));
			autonomousMode = *((std::string *) autoMode.GetSelected());
			
			Wait(0.05);				// wait for a motor update time
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {
		Watchdog &wd = GetWatchdog();
		wd.SetEnabled(true);
		wd.SetExpiration(.5);

		while (IsTest() and IsEnabled()){
//			drive.driveTest();
			wd.Feed();
			Wait(0.05);
		}
		
		robot.robotInit();
		robot.teleop(joystick);
		
	}
};

START_ROBOT_CLASS(CORE2013);

