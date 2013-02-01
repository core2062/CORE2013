#include "CORESubsystemRobot.h"
#include "ShooterSubsystem.h"

PIDCounter::PIDCounter(UINT32 channel):
Counter(channel){
	SetMaxPeriod(.3);  // Value is too high. PID won't stop.
}

double	PIDCounter::PIDGet(){
	if (StatusIsFatal()) return 0.0;
	return (1/GetPeriod());

}

ShooterSubsystem::ShooterSubsystem(void):
shooterMotor(8),
hopperSwitch(1),
feeder(1, Relay::kForwardOnly ), // 0 is relay 1
feederTimer( ),
shooterOptEncoder(10),
shooter360Encoder(14,13),
pid(0.09, 0 ,0, 0.021, &shooterOptEncoder, &shooterMotor)
{
	shooterValue = 0;
	shooterOutput = 0;
	n=0;
	
	shooterOptEncoder.Start();
	shooter360Encoder.Start();
	shooter360Encoder.SetDistancePerPulse(((double) 1.0)/((double) 360.0));
	shooter360Encoder.SetPIDSourceParameter(Encoder::kRate);
	
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
	pid.SetSetpoint(5);
	
	SmartDashboard::PutNumber("P", pid.GetP());
	SmartDashboard::PutNumber("I", pid.GetI());
	SmartDashboard::PutNumber("D", pid.GetD());
	SmartDashboard::PutNumber("F", pid.GetF());
	SmartDashboard::PutNumber("Setpoint", pid.GetSetpoint());
	
	shooterValue = shooterDefault;
	pid.Enable();
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
}

void ShooterSubsystem::teleopOutput(void){
	// service shooter motor
	 pid.SetSetpoint(shooterOutput);
	
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

	SmartDashboard::PutNumber("Shooter speed", shooter360Encoder.GetRate());
	SmartDashboard::PutNumber("Opt Shooter", shooterOptEncoder.PIDGet());
	
	double p = SmartDashboard::GetNumber("P");
	double i = SmartDashboard::GetNumber("I");
	double d = SmartDashboard::GetNumber("D");
	double f = SmartDashboard::GetNumber("F");
	SmartDashboard::PutNumber("Setpoint", shooterOutput);
	
	pid.SetPID(p,i,d,f);
	
//	cout << "  P: " << pid.GetP() << " I: " << pid.GetI() << " D: " << pid.GetD()
//			<< " F: " << pid.GetF() << " Set: " << pid.GetSetpoint() << endl;

	// cout << "we are " << ( feedingDisk ? "feedingDisk" : "not shoooting" ) << endl;		
}
