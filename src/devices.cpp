#include "main.h"
#include "devices.h"
#include "pros/misc.h"
#include "config.h"
pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::MotorGroup leftMotors({-1, -2, -3});
pros::MotorGroup rightMotors({4, 5, 6});
pros::MotorGroup dr4b({7,8});