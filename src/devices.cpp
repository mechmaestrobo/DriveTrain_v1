#include "main.h"
#include "devices.hpp"
#include "pros/misc.h"
#include "config.hpp"
pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::MotorGroup leftMotors({-1, -2, -3});
pros::MotorGroup rightMotors({4, 5, 6});
pros::MotorGroup dr4b({-8,-9});
//pros::adi::DigitalIn dr4b_bumper('A');
//pros::adi::DigitalOut claw('B');