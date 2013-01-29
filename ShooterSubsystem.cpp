#include "CORESubsystemRobot.h"
#include "ShooterSubsystem.h"

PIDCounter::PIDCounter(UINT32 channel):
Counter(channel){}
double	PIDCounter::PIDGet(){
	return(1.0/GetPeriod());
}

ShooterSubsystem::ShooterSubsystem(void):
shooterMotor(8),
hopperSwitch(1),
feeder(1, Relay::kForwardOnly ), // 0 is relay 1
feederTimer( ),
shooterEncoder(3)
{
	shooterValue = 0;
	shooterOutput = 0;
	n=0;
	shooterEncoder.Start();
	pyramidSpeed = false;
	shooterOn = false;
	shooterRunning = false;
	up = false;
	down = false;
	feed = false;
	feedingDisk = false;
}

std::string ShooterSubsystem::name(void)
{
	return "Shooter";
}

void ShooterSubsystem::teleopInit(void)
{
	shooterValue = shooterDefault;
}

void ShooterSubsystem::teleopInput(COREJoystick& joystick){
	pyramidSpeed = joystick.shooterDefault();
	up = joystick.shooterUp();
	down = joystick.shooterDown();
	feed = joystick.shooterShoot();
	shooterOn = joystick.shooterOn();
}

void ShooterSubsystem::teleopLogic(void){
	
	
	if (pyramidSpeed) {
		shooterValue = shooterDefault;
	}
	
	if (up) {
		shooterValue += shooterInc;
	}
	
	if (down) {
		shooterValue -= shooterInc;
	}
	
	
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
	if (n >= 50){
		n = 0;
		cout << "Shooter speed is " << shooterEncoder.Get() << endl;
	} else{++n;}
	
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

