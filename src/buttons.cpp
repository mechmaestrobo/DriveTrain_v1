
#include "buttons.hpp"
#include "dr4b_arm.hpp"
#include "devices.hpp"
#include "drive.hpp"
#include "intake.hpp"
#include "auton.hpp"
#include <algorithm>
#include "main.h"
void receiveButtons(){
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
        velMul += 0.2;
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        velMul -= 0.2;
	}
	velMul = std::clamp(velMul, 0.2, 1.0);
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
		angular_kP += .1;
	}
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
		angular_kP += .1;
	}
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
		angular_kI += .1;
	}
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
		angular_kI -= .1;
	}
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)){
		angular_kD -= .1;
	}
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
		angular_kD += .1;
	}

	if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
		testtune();
	}
	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
		claw.use_claw();
	}
	if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
		angular_kP = 0.0;
		angular_kI = 0.0;
		angular_kD = 0.0;
	}
    // Inside main.cpp receiveButtons()
	angular_kP = std::max(0.0, angular_kP);
	angular_kI = std::max(0.0, angular_kI);
	angular_kD = std::max(0.0, angular_kD);
	/*if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
		dr4b_lift.use_claw();
	}*/
}