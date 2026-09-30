#include "main.h"
#include "devices.hpp"
#include "auton.hpp"
#include "drive.hpp"
#include "config.hpp"
#include "telemetry.hpp"
#include "pros/misc.hpp"
#include "dr4b_arm.hpp"
#include <algorithm>



void telemetry_worker(void* param){
	while (true){
		performReading();
		pros::Task::delay(500);
	}
}

void initialize(){
	initializeDrivetrain();
	dr4b_lift.initialize();
	controller.rumble("-");
}

void competition_initialize() {}

void autonomous() {
    // runAuton();
}

void receiveButtons(){
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
        velMul += 0.2;
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        velMul -= 0.2;
	}
	velMul = std::clamp(velMul, 0.2, 1.0);
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
		dr4b_lift.kp += .1;
	}
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
		dr4b_lift.kp -= .1;
	}
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
		dr4b_lift.ki += .1;
	}
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
		dr4b_lift.ki -= .1;
	}
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)){
		dr4b_lift.kd -= .1;
	}
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
		dr4b_lift.kd += .1;
	}
	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        dr4b_lift.set_target(400.0);
    }
	else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        dr4b_lift.set_target(0.0);
	}
    // Inside main.cpp receiveButtons()
	dr4b_lift.kp = std::max(0.0, dr4b_lift.kp);
	dr4b_lift.ki = std::max(0.0, dr4b_lift.ki);
	dr4b_lift.kd = std::max(0.0, dr4b_lift.kd);

	/*if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
		dr4b_lift.use_claw();
	}*/
}

void opcontrol() {
	pros::Task telemetryTask(telemetry_worker, nullptr, "Telemetry Task");
	while(true){
		receiveButtons();
		runDriveTrain();
		dr4b_lift.run_tick();
		pros::delay(delay_ms);
	}
}
