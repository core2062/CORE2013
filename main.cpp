#include "WPILib.h"

#include "CORESubsystemRobot.h"
#include "COREJoystick.h"
#include "Subsystems.h"
#include <string>

#include "InsightLT/InsightLT.h"

class CORE2013 : public SimpleRobot
{
	CORERobot robot;
	COREJoystick joystick;
	
	DriveSubsystem drive;
	ShooterSubsystem shooter;
	ClimbSubsystem climb;
	
	insight::InsightLT display;
	insight::DecimalData disp_userInfo;
	insight::DecimalData disp_batteryVoltage;
	
	Timer insightTime;
	
	SendableChooser autoMode;
	std::string autonomousMode;

public:
	
	CORE2013(void):
		robot(),
		joystick(),
		
		drive(),
		shooter(),
		climb(),
		
		display(insight::TWO_ONE_LINE_ZONES),
		
		insightTime()
	{
		robot.add(drive);
		robot.add(shooter);
		robot.add(climb);
		insightTime.Start();
	}

	void Autonomous(void){
		
	}
	
	void RobotInit(void){
		robot.robotInit();
		SmartDashboard::PutBoolean("Dev on", CORERobot::isDevMode());
		
		autoMode.AddDefault("Do nothing", new std::string("do nothing"));
		autoMode.AddObject("Shooter only", new std::string("shooter only"));
		autoMode.AddObject("Left of pramid", new std::string("left of pyramid"));
		autoMode.AddObject("Right of pyramid", new std::string("right of pyramid"));
		SmartDashboard::PutData("Autonomous mode", &autoMode);
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
	}
};

START_ROBOT_CLASS(CORE2013);

