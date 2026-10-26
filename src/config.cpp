//This is where all of the configuration constants/variables are defined. All variables marked as a const will not change.
#include "main.h"
#include "config.hpp"
#include "pros/misc.h"

const double WHEEL_DIAMETER = 3.25;
const double TRACK_WIDTH = 11.4;
const int delay_ms = 20;
const int HORIZONTAL_DRIFT = 8;
const double dr4b_motor_rpm = 100.0;
const double intake_motor_rpm = 200.0;
const double drivetrain_motor_rpm = 200.0;
//update if necessary
const double vertical_wheel_location = 1.0;
const double strafe_wheel_location = 2.5;