#include "CORESubsystemRobot.h"
#include "ClimbSubsystem.h"

static const float zero = 0.0;
static const float pinf = 1.0 / zero;

static const float lowSpeed = .7;
static const float highSpeed = 1;

static const Segment steps[] = { Segment(lowSpeed, 8),
		Segment(highSpeed, 28.64), Segment(lowSpeed, 36.64), Segment(-lowSpeed,
				28.64), Segment(-highSpeed, 8), Segment(-lowSpeed, 0), Segment(
				lowSpeed, 8), Segment(highSpeed, 28.64), Segment(lowSpeed,
				36.64), Segment(0,pinf)
	};

ClimbSubsystem::ClimbSubsystem(void):
			climbMotor(CORERobot::CLIMBER),
			tiltMotor(CORERobot::TILTER), //the motor for tilting the robot

			tiltPosLimit(CORERobot::TILT_LIMIT_POSITIVE),
			tiltNegLimit(CORERobot::TILT_LIMIT_NEGATIVE),
			climbTopLimit(CORERobot::CLIMB_LIMIT_TOP),
			climbBottomLimit(CORERobot::CLIMB_LIMIT_BOTTOM),
			climbEncoder(CORERobot::CLIMB_ENC_A, CORERobot::CLIMB_ENC_B) {
	stepCount = 0;

	// (1 in / 4 teeth) * (22 teeth / 1 revA) * (1 revA / 1 revB) * (22 revB * 54 revC) = (11*11)/(54)
	climbEncoder.SetDistancePerPulse((1 / 360) * ((11 * 11) / 54));
	climbEncoder.Start();
	climbEncoder.Reset();
}

void ClimbSubsystem::robotInit(void) {

}

void ClimbSubsystem::teleopInit(void) {

}

void ClimbSubsystem::teleopInput(COREJoystick& joystick) {
	tilting = joystick.climbTilt();
	isDeTilting = joystick.climbDetilt();
	climbing = joystick.climb();
	reset = joystick.climbReset();
}

void ClimbSubsystem::teleopLogic(void) {
	if (climbBottomLimit.Get()) {
		climbEncoder.Reset();
	}
	if (climbing) {
		if (steps[stepCount].speed > 0) {
			if (climbEncoder.GetDistance() > steps[stepCount].pos) {
				++stepCount;
			}
		} else {
			if (climbEncoder.GetDistance() < steps[stepCount].pos) {
				++stepCount;
			}
		}

		currentSpeed = steps[stepCount].speed;
	} else if (reset) {
		stepCount = 0;
		currentSpeed = -.5;
	} else {
		currentSpeed = 0;
	}
	cout << stepCount << ": " << climbEncoder.GetDistance() << endl;
}

void ClimbSubsystem::teleopOutput(void) {

	//	currentSpeed *= .5;

	if (currentSpeed > 0) {
		climbMotor.Set(climbTopLimit.Get() ? 0 : currentSpeed);
	} else {
		climbMotor.Set(climbBottomLimit.Get() ? 0 : currentSpeed);
	}
	SmartDashboard::PutNumber("Climber Speed", climbMotor.Get());
	SmartDashboard::PutBoolean("Climb top limit", climbTopLimit.Get());
	SmartDashboard::PutBoolean("Climb bottom limit", climbBottomLimit.Get());
	SmartDashboard::PutNumber("Climb stage", stepCount);
	SmartDashboard::PutNumber("Climb position", climbEncoder.Get());
	
	SmartDashboard::PutBoolean("Tilt pos limit", !tiltPosLimit.Get());
	SmartDashboard::PutBoolean("Tilt neg limit", !tiltNegLimit.Get());
	
	SmartDashboard::PutBoolean("Is tilted", !tiltPosLimit.Get());

	float tiltSpeed;

	if (isDeTilting)
		tiltSpeed = .5;
	else
		tiltSpeed = tilting ? -.5 : 0;

	if (tiltSpeed > 0) {
		tiltMotor.Set(!tiltPosLimit.Get() ? 0 : tiltSpeed);
	} else {
		tiltMotor.Set(tiltNegLimit.Get() ? 0 : tiltSpeed);
	}
}
