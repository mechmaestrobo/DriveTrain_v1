#include "main.h"
#include "pros/misc.h"
#include "drive.hpp"
#include "devices.hpp"
#include "config.hpp"
#include <algorithm>
#include <cmath>

void initializeDrivetrain() {
    leftMotors.set_brake_mode(pros::v5::MotorBrake::coast);
    rightMotors.set_brake_mode(pros::v5::MotorBrake::coast);
    leftMotors.set_gearing(pros::v5::MotorGears::green);
    rightMotors.set_gearing(pros::v5::MotorGears::green);
}
void runDriveTrain(){
    //read inputs
    double joystickForward = static_cast<double>(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) / 127.0;
    double joystickTurn = static_cast<double>(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) / 127.0;
    //smooth joystick deadzone. The deadzone accounts for drift, however it jerks right when it goes past the deadzone.
    //This stretches the -1 to -0.1 range and 0.1 to 1 range back to -1 to 1, so it you have full control of the speed
    if (std::abs(joystickForward) < .1){
        joystickForward = 0;
    }
    else{
        joystickForward -= (joystickForward > 0? .1: -.1);
        joystickForward /= .9;
    }
    if (std::abs(joystickTurn) < .1){
        joystickTurn = 0;
    }
    else{
        joystickTurn -= (joystickTurn > 0? .1: -.1);
        joystickTurn /= .9;
    }
    //square the speeds so fine movement is easier and is smoother
	double forwardSpeed = joystickForward * std::abs(joystickForward) * velMul;
	double turnSpeed = joystickTurn * std::abs(joystickTurn) *  velMul;
    //calculate the raw speeds
    double leftRaw = forwardSpeed + turnSpeed;
    double rightRaw = forwardSpeed  - turnSpeed;
    //slow it down correctly so it can adjust to the proper turn radius
    double maxRaw = std::max(std::abs(leftRaw), std::abs(rightRaw));
    if(maxRaw > 1.0){
        leftRaw /= maxRaw;
        rightRaw /= maxRaw;
    }
    //calculate voltage
	int leftVoltage = static_cast<int>(leftRaw * 12000);
    int rightVoltage = static_cast<int>(rightRaw * 12000);
	leftMotors.move_voltage(leftVoltage);
	rightMotors.move_voltage(rightVoltage);
} 