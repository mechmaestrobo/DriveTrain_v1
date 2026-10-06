#include "main.h"
#include "intake.hpp"
#include "devices.hpp"
#include "config.hpp"
Intake::Intake(){
        int velocity;
}
void Intake::initialize(){
    
    intakeMotor.set_gearing(pros::v5::MotorGears::red);
    intakeMotor.set_brake_mode(pros::v5::MotorBrake::hold);
}
void Intake::intake(int vel = 0){
    
    velocity = vel;
    intakeMotor.move_velocity(velocity);
}
void Intake::outtake(int vel = 0){
    velocity = -vel;
    intakeMotor.move_velocity(velocity);
}
void Intake::stop(){
    velocity = 0;
    intakeMotor.move_velocity(velocity);
}
int Intake::read_velocity(){
    return velocity;
}