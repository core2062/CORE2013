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
	LiftSubsystem lift;
	
public:
	
	CORE2013(void):
		robot(),
		joystick(),
		
		drive(),
		shooter(),
		lift()
		
	{
		robot.add(drive);
		robot.add(shooter);
		robot.add(lift);
	}

	void Autonomous(void){
		// myRobot.SetSafetyEnabled(false);
	}

	void OperatorControl(void){
		Watchdog &wd = GetWatchdog();
		wd.SetEnabled(true);
		wd.SetExpiration(.5);
		cout <<"before" <<endl;
		robot.teleopInit();
		cout<<"after"<<endl;
		
		while (IsOperatorControl() and !IsDisabled()){
			wd.Feed();
			robot.teleop(joystick);
						
			Wait(0.005);				// wait for a motor update time
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {
		
	}
};

START_ROBOT_CLASS(CORE2013);

