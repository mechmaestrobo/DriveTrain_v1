#include "main.h"
#include "pros/misc.hpp"
#include "devices.hpp"
#include "telemetry.hpp"
#include "config.hpp"
#include "dr4b_arm.hpp"
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>

void performReading(){
    
    pros::Task::delay(50);
    static int lastRumbleTime = 0;
    int currentTime = pros::millis();
    
    std::vector<double> leftMotorTemps = leftMotors.get_temperature_all();
    std::vector<double> rightMotorTemps = rightMotors.get_temperature_all();
    
    double leftMax = *std::max_element(leftMotorTemps.begin(), leftMotorTemps.end());
    double rightMax = *std::max_element(rightMotorTemps.begin(), rightMotorTemps.end());
    double max = std::max(leftMax, rightMax);
    
    controller.print(0, 0, "dp %.1f tp %.1f", dr4b_lift.position, dr4b_lift.target_position);
    
    if (max >= 55.0 && (currentTime - lastRumbleTime > 10000)) {
        controller.rumble("- -"); 
        lastRumbleTime = currentTime;
    }
    
    pros::Task::delay(50);
    
    std::vector<double> leftSpeeds = leftMotors.get_actual_velocity_all();
    std::vector<double> rightSpeeds = rightMotors.get_actual_velocity_all();
    
    double leftSum = std::accumulate(leftSpeeds.begin(), leftSpeeds.end(), 0.0);
    double rightSum = std::accumulate(rightSpeeds.begin(), rightSpeeds.end(), 0.0);
    double totalMotors = static_cast<double>(leftSpeeds.size() + rightSpeeds.size());
    double avg_speed = (leftSum + rightSum) / totalMotors;
    
    controller.print(1, 0, "S %.0f", avg_speed);
    
    pros::Task::delay(50);
    
    //controller.print(2, 0, "Battery: %.0f%%", pros::battery::get_capacity());
    controller.print(2, 0, "P:%.2f I:%.1f D:%.1f G:%.1f", dr4b_lift.kp, dr4b_lift.ki, dr4b_lift.kd, dr4b_lift.kg);
    pros::Task::delay(50);
}
