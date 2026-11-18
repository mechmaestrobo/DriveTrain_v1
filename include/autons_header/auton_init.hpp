#pragma once
#include "lemlib/api.hpp"
void auton_initialize(void);
extern lemlib::Chassis chassis;
extern double angular_kP;
extern double angular_kI;
extern double angular_kD;