#include "main.h"
#include "devices.hpp"
#include "dr4b_arm.hpp"
#include "intake.hpp"
#include "pros/misc.h"
#include "config.hpp"
pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::MotorGroup leftMotors({-1, -3, -5});
pros::MotorGroup rightMotors({2, 4, 6});
pros::MotorGroup dr4b({-8,9});
//pros::adi::DigitalIn dr4b_bumper('A');
pros::adi::DigitalOut claw('A');
pros::Motor wristMotor{10};
pros::Imu imu(7);
pros::Rotation vertical(15); //forward backward encoder
pros::Rotation strafe(16); // left right encoder
pros::Motor intakeMotor{11};
DR4B_ARM dr4b_lift;
Intake intake;