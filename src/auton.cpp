
#include "main.h"
#include "pros/misc.h"
#include "drive.hpp"
#include "devices.hpp"
#include "config.hpp"
#include "auton.hpp"
#include <cmath>
#include <algorithm>
#include "lemlib/api.hpp"
//will be added later
lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, TRACK_WIDTH, lemlib::Omniwheel::NEW_325, 333, HORIZONTAL_DRIFT);
lemlib::TrackingWheel vertical_tracking_wheel(&vertical, WHEEL_DIAMETER, vertical_wheel_location);
lemlib::TrackingWheel strafe_tracking_wheel(&strafe, WHEEL_DIAMETER, strafe_wheel_location);
lemlib::OdomSensors sensors(
&vertical_tracking_wheel, 
nullptr, 
&strafe_tracking_wheel, 
nullptr, 
&imu
);
// lateral PID
double angular_kP = 0;
double angular_kI = 0;
double angular_kD = 0;
lemlib::ControllerSettings lateral_controller(
    0, //kP
    0, //kI
    0, // kD
    3, // anti windup
    1, // small error range, in "
    100, // small error range timeout, in ms
    3, // large error range, in ""
    500, // large error range timeout, in mis
    0 // maximum acceleration (slew)
);

// angular PID
lemlib::ControllerSettings angular_controller(
    angular_kP, // proportional gain (kP)
    angular_kI, // integral gain (kI)
    angular_kD, // derivative gain (kD)
    3, // anti windup
    1, // small error range, in degrees
    100, // small error range timeout, in milliseconds
    3, // large error range, in degrees
    500, // large error range timeout, in milliseconds
    0 // maximum acceleration (slew)
);
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors);
bool tmpflag = false;
void auton_initialize(){
    imu.reset();
    vertical.reset_position();
    strafe.reset_position();
    chassis.resetLocalPosition();
    chassis.calibrate();

}
void runAuton(){
    chassis.setPose(0, 0, 0);
    
}
void testtune(){
    if(tmpflag == false){
        chassis.turnToHeading(90, 10000);
    }
    else(tmpflag == true){
        chassis.turnToHeading(0, 10000);
    }
}