#pragma once
#include "main.h"
#include "pros/misc.h"
#include "dr4b_arm.hpp"
#include "intake.hpp"
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;
extern pros::MotorGroup dr4b;
extern pros::Controller controller;
extern pros::adi::DigitalIn dr4b_bumper;
extern pros::adi::DigitalOut claw;
extern pros::Motor wristMotor;
extern pros::Imu imu;
extern pros::Rotation vertical; //forward backward encoder
extern pros::Rotation strafe; // left right encoder
extern DR4B_ARM dr4b_lift;
extern Intake intake;
extern pros::Motor intakeMotor;
