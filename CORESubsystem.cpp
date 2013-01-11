#include <stdio.h>
#include "WPILib.h"
#include "CORESubsystem.h"
#include <string>

CORESubsystem::CORESubsystem(void){
	name = "undefined name";
}

// Called before loop at start of Teleop period
void CORESubsystem::teleop_init(void){
	printf("Unimplemented teleop_init\n");
}

//Called sequentially during loop, interleaved with other subsystems
void CORESubsystem::teleop_joystick(COREJoystick& joystick){
	printf("Unimplemented teleop_joystick\n");
}
void CORESubsystem::teleop_main(void){
	printf("Unimplemented teleop_main\n");
}
void CORESubsystem::teleop_motors(void){
	printf("Unimplemented teleop_motors\n");
}
