#include "WPILib.h"
#include "COREJoystick.h"
#include <string>
#include <vector>

#ifndef _CORESubsystemRobot_
#define _CORESubsystemRobot_
	

class CORESubsystem {
	
public:
					CORESubsystem(void);
	virtual 		~CORESubsystem(void){};	// class destructor defined to suppress compiler error
	virtual void	teleopInit(void) = 0;	
	virtual void	teleopInput(COREJoystick&) = 0;
	virtual void	teleopLogic(void) = 0;
	virtual void	teleopOutput(void) = 0;
	
	virtual std::string name(void) = 0;
};

class CORERobot {
	vector <CORESubsystem*> subsystems;
	Timer timer;
	
public:	
//	#define _PRACTICE_ // Uncomment for Practice Robot

	#ifndef _PRACTICE_
		// Real robot
			typedef enum {
			DRIVE_RIGHT_ENC_A = 1,
			DRIVE_RIGHT_ENC_B = 2,
			
			DRIVE_LEFT_ENC_A = 3,
			DRIVE_LEFT_ENC_B = 4,
			
			TILT_LIMIT = 8, 	// Need wiring	
			HOPPER_SWITCH = 9,	// Need wiring	
			SHOOTER_OPTICAL = 10
		}input;
	
		typedef enum {
			DRIVE_LEFT_FRONT = 3,
			DRIVE_LEFT_REAR = 4,
	
			DRIVE_RIGHT_FRONT = 5,
			DRIVE_RIGHT_REAR = 6,
			
			TILTER = 7,
			SHOOTER = 8,
			CLIMBER = 9
		}output;
	
	#else
		// Practice robot
		/*
		 * Top Shooter		8
		 * Bottom Shooter	7
		 * Empty 			2, 6
		 * 
		 * Digital I/O
		 * Empty			3, 5, 8, 11, 12
		 * Top				14, 13
		 * Bottom			2, 1
		 */

		// Practice robot
		typedef enum {
			DRIVE_RIGHT_ENC_A = 2,
			DRIVE_RIGHT_ENC_B = 1,
			
			DRIVE_LEFT_ENC_A = 14,
			DRIVE_LEFT_ENC_B = 13,
			
			TILT_LIMIT = 8,
			HOPPER_SWITCH = 11,
			SHOOTER_OPTICAL = 12
		}input;
	
		typedef enum {
			DRIVE_LEFT_FRONT = 7,
			DRIVE_LEFT_REAR = 8,
	
			DRIVE_RIGHT_FRONT = 2,
			DRIVE_RIGHT_REAR = 6,
			
			TILTER = 17,
			SHOOTER = 18,
			CLIMBER = 19
		}output;
	#endif // _PRACTICE_
	
	CORERobot(void);
	void add(CORESubsystem&);
	void teleopInit(void);
	void teleop(COREJoystick&);
	static void console( );
};

#endif
