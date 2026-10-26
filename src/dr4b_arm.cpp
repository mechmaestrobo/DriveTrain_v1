//TODO: fix innacurate position. dr4b moving weirdly and position tracker inacurate. may be due to hardware, slop, or a program issue.
#include "dr4b_arm.hpp"
#include "devices.hpp"
#include "config.hpp"
#include <cmath>
#include <numeric>

DR4B_ARM::DR4B_ARM(){
    kp = 0.0;
    ki = 0.0;
    kd = 0.0;
    target_position = 0.0;
    position = 0.0;
    prev_error = 0.0;
    power = 0.0;
    error = 0.0;
    claw_opened = false;
    integral_sum = 0.0;
}

void DR4B_ARM::initialize() {
    kp = 0.0;
    ki = 0.0;
    kd = 0.0;
    dr4b.set_gearing(pros::v5::MotorGears::red);
    dr4b.set_brake_mode(pros::v5::MotorBrake::hold);
    dr4b.set_encoder_units(pros::v5::MotorUnits::degrees);
    dr4b.tare_position_all();
}

void DR4B_ARM::run_tick() {
    if (!std::isfinite(position)) position = -40.0;
    if (!std::isfinite(error)) error = 0.0;
    if (!std::isfinite(power)) power = 0.0;
    
    auto positions = dr4b.get_position_all();
    
    if (!positions.empty() && positions.size() > 0) {
        double sum = 0.0;
        size_t count = 0;
        for (double pos : positions) {
            if (std::isfinite(pos)) {
                sum += pos;
                count++;
            }
        }
        if (count > 0) {
            position = (((1.0 / 3.0) * (sum / static_cast<double>(count))) - 40.0);
        }
    } 
    
    if (!std::isfinite(position)) position = -40.0;
    
    PID();
    dr4b.move_voltage(power);
}

void DR4B_ARM::PID() {
    error = target_position - position;
    
    if (!std::isfinite(error)) {
        power = 0.0;
        prev_error = 0.0;
        return;
    }
    
    double proportional = kp * error;
    
    if (std::abs(error) < 100.0) {
        integral_sum += error;
        if (integral_sum > 2000.0) integral_sum = 2000.0;
        if (integral_sum < -2000.0) integral_sum = -2000.0;
    } else {
        integral_sum = 0.0;
    }
    double integral = ki * integral_sum;
    
    double derivative = 0.0;
    if (std::isfinite(prev_error)) {
        derivative = kd * (error - prev_error);
    }

    double total_output = proportional + integral + derivative;
    
    if (std::isfinite(total_output) && dr4b_motor_rpm > 0.0) {
        power = (total_output / dr4b_motor_rpm) * 12000.0;
    } else {
        power = 0.0;
    }
    
    if (power > 12000.0) power = 12000.0;
    if (power < -12000.0) power = -12000.0;
    
    prev_error = error;
}

void DR4B_ARM::stop() {
    dr4b.move_voltage(0);
}

void DR4B_ARM::reset() {
    error = 0.0;
    prev_error = 0.0;
    integral_sum = 0.0;
}

void DR4B_ARM::set_target(double new_target) {
    target_position = new_target;
}
