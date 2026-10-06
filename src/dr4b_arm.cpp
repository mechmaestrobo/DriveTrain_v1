#include "dr4b_arm.hpp"
#include "devices.hpp"
#include "config.hpp"
#include <cmath>
#include <numeric>



DR4B_ARM::DR4B_ARM(){
    kp = 0.0;
    ki = 0.0;
    kd = 0.0;
    kg = 0.0;
    target_position = 0.0;
    position = 0.0;
    prev_error = 0.0;
    power = 0.0;
    error = 0.0;
    claw_opened = false;
    integral_sum = 0.0;
}

void DR4B_ARM::initialize() {
    dr4b.set_gearing(pros::v5::MotorGears::red);
    dr4b.set_brake_mode(pros::v5::MotorBrake::hold);
    dr4b.set_encoder_units(pros::v5::MotorUnits::degrees);
    dr4b.tare_position_all();
}

void DR4B_ARM::run_tick() {
    std::vector<double> positions = dr4b.get_position_all();
    
    double sum = std::accumulate(positions.begin(), positions.end(), 0.0);
    if(positions.empty()){
        position = -80.0;
    }
    else {
        position = ((1.0/3.0)*(sum / positions.size()) - 80.0);
    }
    
    PID();
    dr4b.move_velocity(power);
    
    prev_error = error; 
}



void DR4B_ARM::stop() {
    dr4b.move_velocity(0);
}

void DR4B_ARM::PID() {
    error = target_position - position;
    
    double proportional = kp * error; 
    
    if (std::abs(error) < 50.0) {
        integral_sum += error;
    } else {
        integral_sum = 0.0;
    }
    double integral = ki * integral_sum;

    double derivative = kd * (error - prev_error); 
    double gravity = kg * std::cos(position * (M_PI/180.0));
    power = proportional + integral + derivative + gravity;
    
    if (power > dr4b_motor_rpm) {
        power = dr4b_motor_rpm;
    } else if (power < -dr4b_motor_rpm) {
        power = -dr4b_motor_rpm;
    }
}

void DR4B_ARM::reset() {
    error = 0.0;
    prev_error = 0.0;
    integral_sum = 0.0;
}

void DR4B_ARM::set_target(double new_target) {
    target_position = new_target;
}
