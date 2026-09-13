#include "main.h"
#include "devices.h"
#include "auton.h"
#include "drive.h"
#include "config.h"
#include "telemetry.h"
#include "pros/misc.h"
#include "dr4b.h"
#include <algorithm>

void telemetry_worker(void*param){
	while (true){
		performReading();
		pros::delay(400);
	}
}
void initialize(){
	initializeDrivetrain();
	controller.rumble("-");
	
}
void competition_initialize() {}

void autonomous() {
    //runAuton();
}
void receiveButtons(){
	double change = .2 * (
		controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP) -
		controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)
	);
	velMul += change;
	velMul = std::clamp(velMul, .2, 1.0);
	if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
		dr4bUp();
	}
	else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
		dr4bDown();
	}
	else{
		dr4bStop();
	}
}
void opcontrol() {
	pros::Task telemetryTask(telemetry_worker, nullptr, "Telemetry Task");
	while(true){
		receiveButtons();
		runDriveTrain();
		
		pros::delay(10);
	}
}