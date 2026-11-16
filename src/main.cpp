//the control center. all the initialization happens,edit

#include "main.h"
#include "devices.hpp"
#include "auton.hpp"
#include "drive.hpp"
#include "config.hpp"
#include "telemetry.hpp"
#include "pros/misc.hpp"
#include "dr4b_arm.hpp"
#include "intake.hpp"
#include <algorithm>
#include "buttons.hpp"


void telemetry_worker(void* param){
	while (true){
		pros::Task::delay(500);
		performReading();
		
	}
}




void initialize(){
	initializeDrivetrain();
	controller.clear();
	//dr4b_lift.initialize();
	controller.rumble("-");
	//dr4b_lift.set_target(-80.0);
	pros::delay(50);
}

void competition_initialize() {}
void autonomous() {
    // runAuton();
}



void opcontrol() {
	pros::delay(50);
	pros::Task telemetryTask(telemetry_worker, nullptr, "Telemetry Task");
	while(true){
		receiveButtons();
		runDriveTrain();
		//dr4b_lift.run_tick();
		pros::delay(delay_ms);
	}
}
