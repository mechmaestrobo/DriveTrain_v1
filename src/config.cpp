#include "main.h"
#include "config.hpp"
#include "pros/misc.h"
double velMul = 1;
const double WHEEL_DIAMETER = 3.25;
const double TRACK_WIDTH = 11.4;
const int delay_ms = 20;
const int HORIZONTAL_DRIFT = 8;
double dr4b_motor_rpm = 100.0;
double intake_motor_rpm = 200.0;
double drivetrain_motor_rpm = 200.0;
//update
double vertical_wheel_location = 0.0;
double strafe_wheel_location = 0.0;