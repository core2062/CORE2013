#include "WPILib.h"
#include "COREJoystick.h"

	COREJoystickButton::COREJoystickButton( Joystick * jPtr, int	num )
	{
		joystick = jPtr;
		input = num;
		
		state = oldState = false;
		
	}
	
	// returns current state
	bool COREJoystickButton::Get(){
	
		return( joystick->GetRawButton( input ) );
	}
	
	// returns true on rising edge
	bool COREJoystickButton::Rise(){
		
		state = Get();

		bool rise = state and !oldState;
		
		oldState = state;
		
		return( rise );
	}
	
 // returns false on rising edge
	bool COREJoystickButton::Fall(){
		
		state = Get();

		bool fall = !state and oldState;
		
		oldState = state;
		
		return( fall );
		
	}
