#include "COREDrive.h"

void COREDrive::ColinArcade(double mag, double rotate){
	double right = (mag-rotate)/2;
	double left = (mag+rotate)/2;
	SetLeftRightMotorOutputs(left, right);
}

double inline etherL(double fwd, double rcw, double a, double b){
	return fwd + b*rcw*(1-fwd);
}

double inline etherR(double fwd, double rcw, double a, double b){
	return fwd-b*rcw + fwd*rcw*(b-a-1);
}

void COREDrive::EtherArcade(double mag, double rotate, double a, double b){
	double left;
	double right;
	if (mag>=0){
		if (rotate>=0){
			left = etherL(mag, rotate, a, b);
			right = etherR(mag, rotate, a, b);
		} else{
			left = etherR(mag, -rotate, a, b);
			right = etherL(mag, -rotate, a, b);
		}
	} else{
		if (rotate>=0){
			left = -etherL(-mag, rotate, a, b);
			right = -etherR(-mag, rotate, a, b);
		} else{
			left = -etherR(-mag, -rotate, a, b);
			right = -etherL(-mag, -rotate, a, b);
		}
	}
	SetLeftRightMotorOutputs(left, right);
}

/*
 Ether:
 
 Arcade algorithm to compute left and right wheel commands 
 from forward and rotate-clockwise joystick commands.

  "fwd" is the Forward command (-1 to +1);
  "rcw" is the Rotate Clockwise command (-1 to +1);
  "a" and "b" are tuning parameters:
  a is the amount to turn at 100% fwd in the range 0 to 1;
  b is the amount to turn at   0% fwd in the range 0 to 1;
  when a=0 and b=1 this gives you the WPILib arcade behavior;


function L(fwd,rcw,a,b: float): float;
begin
L := fwd + b*rcw*(1-fwd);
end;

function R(fwd,rcw,a,b: float): float;
begin
R := fwd - b*rcw + fwd*rcw*(b-a-1);
end;

procedure LR(fwd,rcw,a,b: float; var left,right: float);
begin
if fwd>=0 then
 begin
 if rcw>=0 then
  begin {Q1}
  left := L(fwd,rcw,a,b);
  right := R(fwd,rcw,a,b);
  end
 else
  begin {Q2}
  left := R(fwd,-rcw,a,b);
  right := L(fwd,-rcw,a,b);
  end
 end
else
 begin
 if rcw>=0 then
  begin {Q4}
  left := -R(-fwd,rcw,a,b);
  right := -L(-fwd,rcw,a,b);
  end
 else
  begin {Q3}
  left := -L(-fwd,-rcw,a,b);
  right := -R(-fwd,-rcw,a,b);
  end
 end;
end;
*/