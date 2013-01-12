#include "WPILib.h"

#include "Subsystems.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	CORERobot robot;
	COREJoystick joystick;
	
public:
	RobotDemo(void):
		robot(),
		joystick()
	{
		
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void){
		// myRobot.SetSafetyEnabled(false);
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void){
		Watchdog &wd = GetWatchdog();
		wd.SetEnabled(true);
		wd.SetExpiration(.5);
		
		robot.teleop_init();
		
		while (IsOperatorControl() and !IsDisabled()){
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

START_ROBOT_CLASS(RobotDemo);

