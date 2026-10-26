//These are where all of the motors, ports, and subsytems are defined(basically the electronics)
#include "main.h"
#include "devices.hpp"
#include "dr4b_arm.hpp"
#include "intake.hpp"
#include "pros/misc.h"
#include "config.hpp"
#include "claw.hpp"
pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::MotorGroup leftMotors({-11, -13, -15});
pros::MotorGroup rightMotors({12, 14, 16});
pros::MotorGroup dr4b({18,-19});
//pros::adi::DigitalIn dr4b_bumper('A');
pros::adi::Pneumatics claw_piston('A', false);
pros::Motor wristMotor{20};
pros::Imu imu(17);
pros::Rotation vertical(15); //forward backward encoder
pros::Rotation strafe(16); // left right encoder
pros::Motor intakeMotor{11};
DR4B_ARM dr4b_lift;
Intake intake;
Claw claw;