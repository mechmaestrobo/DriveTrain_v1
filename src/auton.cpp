#include "main.h"
#include "pros/misc.h"
#include "drive.hpp"
#include "devices.hpp"
#include "config.hpp"
#include "auton.hpp"
#include <cmath>
#include <algorithm>
//will be added later
lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, TRACK_WIDTH, lemlib::Omniwheel::NEW_325, 333, HORIZONTAL_DRIFT);
lemlib::TrackingWheel vertical_tracking_wheel(&vertical, WHEEL_DIAMETER, 0);//replace with horizontal distance to center
lemlib::TrackingWheel strafe_tracking_wheel(&strafe, WHEEL_DIAMETER, 0); //replace with vertical distance to center
lemlib::OdomSensors sensors(
&vertical_tracking_wheel, 
nullptr, 
&strafe_tracking_wheel, 
nullptr, 
&imu
);
// lateral PID
lemlib::ControllerSettings lateral_controller(
    10, //kP
    0, //kI
    3, // kD
    3, // anti windup
    1, // small error range, in "
    100, // small error range timeout, in ms
    3, // large error range, in ""
    500, // large error range timeout, in mis
    0 // maximum acceleration (slew)
);

// angular PID
lemlib::ControllerSettings angular_controller(
    2, // proportional gain (kP)
    0, // integral gain (kI)
    10, // derivative gain (kD)
    3, // anti windup
    1, // small error range, in degrees
    100, // small error range timeout, in milliseconds
    3, // large error range, in degrees
    500, // large error range timeout, in milliseconds
    0 // maximum acceleration (slew)
);
void runAuton(){
    

}