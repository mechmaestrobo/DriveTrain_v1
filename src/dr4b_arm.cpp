//TODO: fix innacurate position. dr4b moving weirdly and position tracker inacurate. may be due to hardware, slop, or a program issue.
/*#include "dr4b_arm.hpp"
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
    kp = 150.0;
    kpdown = 0.0;
    dir = true;
    ki = 2.0;
    kidown = 0.0;
    kd = 2.0;
    kddown = 0.0;
    dr4b.set_gearing(pros::v5::MotorGears::red);
    dr4b.set_brake_mode(pros::v5::MotorBrake::coast);
    dr4b.set_encoder_units(pros::v5::MotorUnits::degrees);
    dr4b.tare_position_all(); // Encoders are now firmly 0.0 at the absolute bottom
}

void DR4B_ARM::run_tick() {
    if (!std::isfinite(position)) position = -80.0;
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

            double raw_degrees = sum / static_cast<double>(count);
            
     
            double raw_floor = 0.0;
            double raw_horizontal = 234.0; 
            double raw_peak = 374.0;
            
            if (raw_degrees <= raw_horizontal) {
                double t = (raw_degrees - raw_floor) / (raw_horizontal - raw_floor);
                if (t < 0.0) t = 0.0;
                position = -80.0 + (80.0 * t);
            } else {
               
                double t = (raw_degrees - raw_horizontal) / (raw_peak - raw_horizontal);
                if (t > 1.0) t = 1.0;
                position = 0.0 + (80.0 * t);
            }
        }
    } 
    
    if (!std::isfinite(position)) position = -80.0;
    
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
    
    if (dir == true) {

        double proportional = kp * error;
        double integral = ki * integral_sum;
        double derivative = 0.0;
        if (std::isfinite(prev_error)) {
            derivative = kd * (error - prev_error);
        }
        total_output = proportional + integral + derivative;
    } 
    else {
    
        double proportional_down = kpdown * error;
        double integral_down = kidown * integral_sum;
        double derivative_down = 0.0;
        if (std::isfinite(prev_error)) {
            derivative_down = kddown * (error - prev_error);
        }
        total_output = proportional_down + integral_down + derivative_down;
    }
    if (std::isfinite(prev_error)) {
        derivative = kd * (error - prev_error);
        derivative_down = kddown * (error - prev_error);
    }
    double total_output = 0.0;
    if(dir == true){
        total_output = proportional + integral + derivative;
    }
    else{
        total_output = proportional_down + integral_down + derivative_down;
    }


    if (std::isfinite(total_output)) {
        power = (total_output);
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
*/