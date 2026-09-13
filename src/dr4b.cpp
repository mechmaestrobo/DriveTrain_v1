#include "dr4b.h"
#include "main.h"
#include "devices.h"
#include "pros/motors.h"
void initializeArm(){
    dr4b.set_gearing(pros::E_MOTOR_GEAR_GREEN);
    dr4b.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
void dr4bUp(){
    dr4b.move_voltage(10000);
}
void dr4bDown(){
    dr4b.move_voltage(-10000);
}
void dr4bStop(){
    dr4b.move_voltage(0);
}