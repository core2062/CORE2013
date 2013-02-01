#include "WPILib.h"

#include "CORESubsystemRobot.h"
#include "COREJoystick.h"
#include "Subsystems.h"


class CORE2013 : public SimpleRobot
{
	CORERobot robot;
	COREJoystick joystick;
	
	DriveSubsystem drive;
	ShooterSubsystem shooter;
	ClimbSubsystem climb;
	
public:
	
	CORE2013(void):
		robot(),
		joystick(),
		
		drive(),
		shooter(),
		climb()
		
	{
		robot.add(drive);
		robot.add(shooter);
		robot.add(climb);
	}

	void Autonomous(void){
		// Hey
	}
	
	void Disabled(void){
		cout << "Disabled" << endl;
	}

	void OperatorControl(void){
		Watchdog &wd = GetWatchdog();
		wd.SetEnabled(true);
		wd.SetExpiration(.5);
		
		cout <<"before" <<endl;
		robot.teleopInit();
		cout<<"after"<<endl;
		
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
		
	}
};

START_ROBOT_CLASS(CORE2013);

