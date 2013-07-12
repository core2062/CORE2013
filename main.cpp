#include "WPILib.h"

#include "CORESubsystemRobot.h"
#include "COREJoystick.h"
#include "Subsystems.h"
#include <string>
#include <cmath>
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
	BlockerSubsystem blocker;
//	ClimbSubsystem climb;
	
	insight::InsightLT display;
	insight::StringData disp_timeData;
	insight::DecimalData disp_batteryVoltage;
	
	Timer insightTime;
	
//	SendableChooser autoMode;
//	std::string autonomousMode;

public:
	
	CORE2013(void):
		autoSeq(),
		
		robot(),
		joystick(),
		
		drive(),
		shooter(),
		blocker(),
		
		display(insight::TWO_ONE_LINE_ZONES),
		
		insightTime()
	{
		robot.add(drive);
		robot.add(shooter);
		robot.add(blocker);
		insightTime.Start();
		
		
	}

	void RobotInit(void){
			robot.robotInit();
			SmartDashboard::PutBoolean("Dev on", CORERobot::isDevMode());
			
			SmartDashboard::PutBoolean("wait-before", false);
			SmartDashboard::PutBoolean("backup", false);
			SmartDashboard::PutBoolean("flip", false);
			
			SmartDashboard::PutNumber("Delay time", 5);
			
			SmartDashboard::PutNumber("backup-distance", 12); //48 (changed to be safe until encoders are fixed)
			SmartDashboard::PutNumber("flip-timing", 1.25);
		}

	void Autonomous(void){
		Watchdog &wd = GetWatchdog();
		wd.SetEnabled(false);
		wd.SetExpiration(.5);

		autoSeq = AutoSequencer();
		/* Shooter only actions*/
		ShootAction shoot (shooter, 6);
		DriveAction drive_back (drive, -.7, -SmartDashboard::GetNumber("backup-distance"));
		RotateAction flip (drive, .5, SmartDashboard::GetNumber("flip-timing"));
		WaitAction wait (SmartDashboard::GetNumber("Delay time"));
		WaitAction after (.25);
		if(SmartDashboard::GetBoolean("wait-before")){
			autoSeq.add_action(wait);}
		autoSeq.add_action(shoot);
		autoSeq.add_action(after);
		if(SmartDashboard::GetBoolean("backup")){
			autoSeq.add_action(drive_back);}
		if(SmartDashboard::GetBoolean("flip")){
			autoSeq.add_action(flip);}
		
		
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
		disp_batteryVoltage.setHeader("Battery:");
		disp_timeData.setHeader("Match Time:");
		display.registerData(disp_timeData, 1);
		display.registerData(disp_batteryVoltage, 2);
		display.startDisplay();
		
		while (IsDisabled()){
			disp_batteryVoltage.setData((DriverStation::GetInstance())->GetBatteryVoltage());
			double time = insightTime.Get();
			int minutes = (int)floor(time/60);
			double seconds = fmod(time, 60.0);
			char out [10];
			sprintf(out, "%im %.2fs", minutes, seconds);
			disp_timeData.setData(out);
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

