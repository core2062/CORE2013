#include "CORESubsystemRobot.h"
#include "ShooterSubsystem.h"
#include <cmath>

PIDCounter::PIDCounter(UINT32 channel):
Counter(channel){
	SetMaxPeriod(.10);
}

double	PIDCounter::PIDGet(){
	if (StatusIsFatal()) return 0.0;
	return (1/GetPeriod());

}

ShooterSubsystem::ShooterSubsystem(void):
shooterMotor(CORERobot::SHOOTER),
pusher(CORERobot::PUSHER_MOTOR),
pusherTimer(),
shooterOptEncoder(CORERobot::SHOOTER_OPTICAL),
pid(0.1, .03 ,0, 0.021, &shooterOptEncoder, &shooterMotor, .05)
{
	shooterValue = 0;
	shooterOutput = 0;
	
	pusherOutput = false;
	
	shooterOptEncoder.Start();
	
//	shooter360Encoder.Start();
//	shooter360Encoder.SetDistancePerPulse(((double) 1.0)/((double) 360.0));
//	shooter360Encoder.SetPIDSourceParameter(Encoder::kRate);
	
	pyramidSpeed = false;
	shooterOn = false;
	shooterRunning = false;
	up = false;
	down = false;
	feed = false;
	feedingDisk = false;
	shooterSpeedOverride = false;
	shooterAtSpeed = false;
}

std::string ShooterSubsystem::name(void)
{
	return "Shooter";
}

void ShooterSubsystem::robotInit(void){
	SmartDashboard::PutNumber("P", pid.GetP());
	SmartDashboard::PutNumber("I", pid.GetI());
	SmartDashboard::PutNumber("D", pid.GetD());
	SmartDashboard::PutNumber("F", pid.GetF());
	SmartDashboard::PutNumber("Setpoint", pid.GetSetpoint());
	SmartDashboard::PutBoolean("Shooter speed override", shooterSpeedOverride);
	SmartDashboard::PutBoolean("Shooter at speed", shooterAtSpeed);
}

void ShooterSubsystem::teleopInit(void)
{
//	pid.SetSetpoint(5);

	shooterValue = shooterDefault;
	shooterRunning = false;
}

void ShooterSubsystem::teleopInput(COREJoystick& joystick){
	pyramidSpeed = joystick.shooterDefault();
	up = joystick.shooterUp();
	down = joystick.shooterDown();
	feed = joystick.shooterShoot();
	shooterOn = joystick.shooterOn();
}

void ShooterSubsystem::teleopLogic(void){
	shooterSpeedOverride = SmartDashboard::GetBoolean("Shooter speed override");
	
	if (pusherOutput and pusherTimer.Get() > pushTime) {
		pusherOutput = false;
	} else if ((shooterSpeedOverride or (shooterAtSpeed = std::abs(shooterOptEncoder.PIDGet() - shooterValue) < 1.0)) and feed){
		pusherOutput = true;
		pusherTimer.Reset();
		pusherTimer.Start();
		cout << "I'm shooting!"  << endl;
	}
	
	// Shooter
	if (pyramidSpeed) {
		shooterValue = shooterDefault;
	}
	if (up) {
		if(!shooterRunning){
			shooterOn = true;
		}
		shooterValue += shooterInc;
	}
	if (down) {
		shooterValue -= shooterInc;
	}
	if ( shooterOn and ! shooterRunning ){
		shooterRunning = true;
	}
	else if ( shooterOn and shooterRunning){
		shooterRunning = false;
	}
	if (shooterValue <= 15){
		shooterValue = 16;
	}
	
	if ( shooterRunning )
	{	
		shooterOutput =  shooterValue;
		pid.Enable();
	}
	else
	{
		shooterOutput =  0;
		pid.Disable();
	}
}

void ShooterSubsystem::teleopOutput(void){
	// service shooter motor
	pid.SetSetpoint(shooterOutput);
	
	
	// service pusher
	pusher.Set(pusherOutput ? -1.0 : 0.0);

	cout << "Dev mode is " << CORERobot::isDevMode() << endl;
	// smart dashboard
	if (CORERobot::isDevMode()){
		double p = SmartDashboard::GetNumber("P");
		cout << "Is called " << p << endl;
		double i = SmartDashboard::GetNumber("I");
		double d = SmartDashboard::GetNumber("D");
		double f = SmartDashboard::GetNumber("F");
		pid.SetPID(p,i,d,f);

		
		SmartDashboard::PutNumber("Opt Shooter", shooterOptEncoder.PIDGet());
	}
	SmartDashboard::PutNumber("Setpoint", shooterOutput);
	SmartDashboard::PutBoolean("Shooter at speed", shooterAtSpeed);

	
//	cout << "  P: " << pid.GetP() << " I: " << pid.GetI() << " D: " << pid.GetD()
//			<< " F: " << pid.GetF() << " Set: " << pid.GetSetpoint() << endl;

	// cout << "we are " << ( feedingDisk ? "feedingDisk" : "not shoooting" ) << endl;		
}

void ShooterSubsystem::shoot(float shooterOutput){
	pid.SetSetpoint(shooterOutput);
}

void ShooterSubsystem::push(float pusherOutput){
	pusher.Set(pusherOutput);
}
bool ShooterSubsystem::getUpToSpeed(void){
	return (std::abs(shooterOptEncoder.PIDGet() - shooterValue) < 1.0);
}
