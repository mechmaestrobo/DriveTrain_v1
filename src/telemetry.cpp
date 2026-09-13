#include "main.h"
#include "pros/misc.h"
#include "devices.h"
#include "telemetry.h"
#include "config.h"
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>
void performReading(){
    //rumble
    static int lastRumbleTime = 0;
    int currentTime = pros::millis();
    
    //calculate motor with highest temperature
    std::vector<double> leftMotorTemps = leftMotors.get_temperature_all();
    std::vector<double> rightMotorTemps = rightMotors.get_temperature_all();
    //max_element returns a pointer so we use the * operator to get the value
    double leftMax = *std::max_element(leftMotorTemps.begin(), leftMotorTemps.end());
    double rightMax = *std::max_element(rightMotorTemps.begin(), rightMotorTemps.end());
    double max = std::max(leftMax, rightMax);
    //%.1f will output a double rounded to the tenth. in this case its max
    controller.print(
        0, 0,
        "Temp: %.1f C",
        max
    );
    //rumble if overheated
    if (max >= 55.0 && (currentTime - lastRumbleTime > 10000)) {
        controller.rumble("- -"); 
        lastRumbleTime = currentTime;
    }
    pros::delay(50);
    //get avg speed
    std::vector<double> leftSpeeds = leftMotors.get_actual_velocity_all();
    std::vector<double> rightSpeeds = rightMotors.get_actual_velocity_all();
    //get sum of left and right, then find the avg.
    double leftSum = std::accumulate(leftSpeeds.begin(), leftSpeeds.end(), 0.0);
    double rightSum = std::accumulate(rightSpeeds.begin(), rightSpeeds.end(), 0.0);
    double avg_speed = (leftSum + rightSum) / (4*leftSpeeds.size());
    controller.print(
        1, 0,
        "Speed: %.0f(%%)",
        avg_speed
    );
    pros::delay(50);
    //get battery
    controller.print(
        2, 0,
        "Battery: %.0f%%",
        pros::battery::get_capacity()
    );
}