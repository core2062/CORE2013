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
	virtual void	robotInit(void) = 0;	
	virtual void	teleopInit(void) = 0;	
	virtual void	teleopInput(COREJoystick&) = 0;
	virtual void	teleopLogic(void) = 0;
	virtual void	teleopOutput(void) = 0;
	
	virtual std::string name(void) = 0;
};

class CORERobot
{
	vector <CORESubsystem*> subsystems;
	Timer timer;
	
	static bool developerMode;
	
public:	
//	#define _PRACTICE_ // Uncomment for Practice Robot

	#ifndef _PRACTICE_
		// Real robot
			typedef enum {
			DRIVE_RIGHT_ENC_A = 1,
			DRIVE_RIGHT_ENC_B = 2,
			
			DRIVE_LEFT_ENC_A = 3,
			DRIVE_LEFT_ENC_B = 4,
			
			DRIVE_GYRO = 1,
						
			SHOOTER_OPTICAL = 6,
			BLOCKER_OPTICAL = 7
		}input;
	
		typedef enum {
			DRIVE_LEFT_FRONT = 3,
			DRIVE_LEFT_REAR = 4,
	
			DRIVE_RIGHT_FRONT = 5,
			DRIVE_RIGHT_REAR = 6,
			
			SHOOTER = 8,
			PUSHER_MOTOR = 10,
			
			BLOCKER_WINCH = 1
			
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
			
			DRIVE_LEFT_ENC_A = 3,
			DRIVE_LEFT_ENC_B = 4,
		
			CLIMB_ENC_A = 14,
			CLIMB_ENC_B = 13,
			DRIVE_GYRO = 1,
									
			TILT_LIMIT_POSITIVE = 11,	
			TILT_LIMIT_NEGATIVE = 12,
			SHOOTER_OPTICAL = 10,
			CLIMB_LIMIT_TOP = 8,
			CLIMB_LIMIT_BOTTOM = 9
		}input;
	
		typedef enum {
			DRIVE_LEFT_FRONT = 110,
			DRIVE_LEFT_REAR = 118,
	
			DRIVE_RIGHT_FRONT = 116,
			DRIVE_RIGHT_REAR = 117,
			
			TILTER = 210,
			SHOOTER = 118,
			CLIMBER_ONE = 111,
			CLIMBER_TWO = 111,
			PUSHER_MOTOR = 10
		}output;
	#endif // _PRACTICE_
	
	CORERobot(void);
	void add(CORESubsystem&);
	void robotInit(void);
	void teleopInit(void);
	void teleop(COREJoystick&);
	static void console( );
	static bool isDevMode( );
	static void setDevMode(bool mode);
};

#endif
