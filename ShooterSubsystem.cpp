#include "CORESubsystemRobot.h"
#include "ShooterSubsystem.h"


ShooterSubsystem::ShooterSubsystem(void):
shooterMotor(8),
hopperSwitch(1),
//shooterEncoder(1)
feeder(1, Relay::kForwardOnly ), // 0 is relay 1
feederTimer( )
{
	shooterValue = 0;
	shooterOutput = 0;
	
	// initialize bools
	pyramidSpeed = false;
	oldPyramidSpeed = false;
	shooterOn = false;
	shooterRunning = false;
	up = false;
	oldUp = false;
	down = false;
	oldDown = false;
	feed = false;
	feedingDisk = false;
}

std::string ShooterSubsystem::name(void)
{
	return "Shooter";
}

void ShooterSubsystem::teleopInit(void)
{
//	shooterEncoder.Start();
	
	shooterValue = shooterDefault;
}

void ShooterSubsystem::teleopInput(COREJoystick& joystick){
	pyramidSpeed = joystick.shooterZero();
	up = joystick.shooterUp();
	down = joystick.shooterDown();
	feed = joystick.shooterShoot();
	shooterOn = joystick.shooterOn();
}

void ShooterSubsystem::teleopLogic(void){
	
	// could change this logic to use the new rising edge features in COREJoystickButton
	if (!oldPyramidSpeed && pyramidSpeed) {
		shooterValue = shooterDefault;
	}
	// ditto
	if (!oldUp && up) {
		shooterValue += shooterInc;
	}
	//ditto
	if (!oldDown && down) {
		shooterValue -= shooterInc;
	}
	
	// store old versions
	oldPyramidSpeed = pyramidSpeed;
	oldUp = up;
	oldDown = down;
	
	if (feed and !feedingDisk and shooterRunning ) {
		feederTimer.Reset();
		feederTimer.Start();
		feedingDisk = true;
	}
	
	// shooter on toggles run mode
	if ( shooterOn and ! shooterRunning ){
		shooterRunning = true;
	}
	else if ( shooterOn and shooterRunning){
		shooterRunning = false;
	}
		
	shooterOutput = shooterRunning ? shooterValue : 0;
	
	// cout << "Shooter Output is " << shooterOutput <<endl;
	
}

void ShooterSubsystem::teleopOutput(void){
	// service shooter motor
	shooterMotor.Set(shooterOutput);
	
	// service feeder
	if ( !feedingDisk )
	{
		feeder.Set( Relay::kOff );
	}
	else {
		if ( feederTimer.HasPeriodPassed( feederTime ) ) {
			feedingDisk = false;
			feeder.Set( Relay::kOff );
		}
		else {
			feeder.Set( Relay::kOn );
		}
	}	
	
	// cout << "we are " << ( feedingDisk ? "feedingDisk" : "not shoooting" ) << endl;
		
}

