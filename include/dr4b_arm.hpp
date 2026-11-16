#pragma once

#include "main.h"
#include "dr4b_arm.hpp"
#include <vector>

class DR4B_ARM {
  public:
    DR4B_ARM();

    bool claw_opened;
    void initialize();
    void run_tick();
    
    void stop();
    void reset();
    void set_target(double new_target);
    double kp;
    double ki;
    double kd;
    double target_position;
    double position;
    double kpdown;
    double kidown;
    double kddown;
    double error;
    bool dir;
  private:
    void PID();
    
    double prev_error;
    double power;
    
    double integral_sum;
    
};
