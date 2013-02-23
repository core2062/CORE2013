#include "WPILib.h"

#include "CORESubsystemRobot.h"
#include "COREJoystick.h"
#include "Subsystems.h"

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

			Wait(0.05);				// wait for a motor update time
			SmartDashboard::PutNumber("Teleop time", teleop.Get());
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {
		while (IsTest() and IsEnabled()){
			drive.driveTest();
		}
	}
};

START_ROBOT_CLASS(CORE2013);

