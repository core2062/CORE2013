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

SensorEdge::SensorEdge():
	puckPhotoEye(1,1)
{
	oldState = true;
}

// returns current state
bool SensorEdge::Get(){
	return( puckPhotoEye.GetVoltage() < .5 );
}

float SensorEdge::GetVoltage(){
	return puckPhotoEye.GetVoltage();
}

// returns true on rising edge
bool SensorEdge::Rise(){
	
	bool state = Get();
	bool rise = state and !oldState;
	cout << rise << ": (" << state << " and not " << oldState << ")"<< endl;
	oldState = state;
	return( rise );
}
// returns false on rising edge
bool SensorEdge::Fall(){
	
	bool state = Get();
	bool fall = !state and oldState;
	oldState = state;
	return( fall );
	
}

ShooterSubsystem::ShooterSubsystem(void):
shooterMotor(CORERobot::SHOOTER),
pusher(CORERobot::PUSHER_MOTOR),
pusherTimer(),
shooterOptEncoder(CORERobot::SHOOTER_OPTICAL),
//pid(0.13, .03 ,0, 0.018, &shooterOptEncoder, &shooterMotor, .05),
pid(0.1, 0 ,0, 0.013, &shooterOptEncoder, &shooterMotor, .05),
pusherSensor()
{
	shooterValue = 0;
	shooterOutput = 0;
	
	pusherOutput = 0;
	pid.SetOutputRange(0,1);
	shooterOptEncoder.Start();
	
//	shooter360Encoder.Start();
//	shooter360Encoder.SetDistancePerPulse(((double) 1.0)/((double) 360.0));
//	shooter360Encoder.SetPIDSourceParameter(Encoder::kRate);
	
	pyramidSpeed = false;
	shooterOn = false;
	shooterRunning = false;
	up = false;
	down = false;
	feed = 0;
	isFeeding = false;
	shooterSpeedOverride = false;
	shooterAtSpeed = false;
}

std::string ShooterSubsystem::name(void)
{
	return "Shooter";
}

void ShooterSubsystem::robotInit(void){
	pid.SetSetpoint(0);
	pid.Enable();
	SmartDashboard::PutNumber("P", pid.GetP());
	SmartDashboard::PutNumber("I", pid.GetI());
	SmartDashboard::PutNumber("D", pid.GetD());
	SmartDashboard::PutNumber("F", pid.GetF());
	SmartDashboard::PutNumber("Setpoint", pid.GetSetpoint());
	SmartDashboard::PutBoolean("Shooter speed override", shooterSpeedOverride);
	SmartDashboard::PutBoolean("Shooter at speed", shooterAtSpeed);
	SmartDashboard::PutNumber("p-mul", .5);
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
	feed = joystick.shooterShoot() ? 1 : 0;
	
	feed = joystick.shooterBackwards() ? -1 : feed;
	shooterOn = joystick.shooterOn();
}

void ShooterSubsystem::teleopLogic(void){
	shooterSpeedOverride = SmartDashboard::GetBoolean("Shooter speed override");
	
	shooterAtSpeed = std::abs(shooterOptEncoder.PIDGet() - shooterValue) < 1;
	
	cout << feed << " " << isFeeding << " " << endl;
	SmartDashboard::PutNumber("photo", pusherSensor.GetVoltage()*1000);
	if (isFeeding) {
	    if (pusherSensor.Fall()) {
	        pusherOutput = 0;
	        isFeeding = false;
	    } else {
	        pusherOutput = pusherOutput;
	        isFeeding = true;
	    }
	} else {
	    if ((feed == -1) or (feed == 1)) {
	        if (shooterSpeedOverride or shooterAtSpeed) {
	            pusherOutput = feed;
	            isFeeding = true;
	        } else {
	            pusherOutput = 0;
	            isFeeding = false;
	        }
	    } else {
	        pusherOutput = 0;
	        isFeeding = false;
	    }
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
//		pid.Enable();
	}else{
		shooterOutput =  0;
//		pid.Disable();
	}
}

void ShooterSubsystem::teleopOutput(void){
	// service shooter motor
	pid.SetSetpoint(shooterOutput);
	
	
	// service pusher
	float pm = SmartDashboard::GetNumber("p-mul");
	pusher.Set(((float) -pusherOutput) * pm);

	if (CORERobot::isDevMode()){
		double p = SmartDashboard::GetNumber("P");
		cout << "Is called " << p << endl;
		double i = SmartDashboard::GetNumber("I");
		double d = SmartDashboard::GetNumber("D");
		double f = SmartDashboard::GetNumber("F");
		pid.SetPID(p,i,d,f);

		
		SmartDashboard::PutNumber("Opt Shooter", shooterOptEncoder.PIDGet());
		SmartDashboard::PutNumber("pusher-output", pusherOutput);
	}
	SmartDashboard::PutNumber("Setpoint", shooterOutput);
	SmartDashboard::PutBoolean("Shooter at speed", shooterAtSpeed);

	
//	cout << "  P: " << pid.GetP() << " I: " << pid.GetI() << " D: " << pid.GetD()
//			<< " F: " << pid.GetF() << " Set: " << pid.GetSetpoint() << endl;

	// cout << "we are " << ( feedingDisk ? "feedingDisk" : "not shoooting" ) << endl;		
}

void ShooterSubsystem::shoot(float shooterOutput){
	pid.SetSetpoint(shooterOutput * (shooterDefault));
}

void ShooterSubsystem::push(float pusherOutput){
	pusher.Set(-pusherOutput);
}
bool ShooterSubsystem::getUpToSpeed(void){
	return (std::abs(shooterOptEncoder.PIDGet() - shooterValue) < 1.0);
}
