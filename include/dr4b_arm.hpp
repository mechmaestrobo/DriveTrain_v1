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
    void use_claw();
    void stop();
    void reset();
    void set_target(double new_target);
    double kp;
    double ki;
    double kd;
    double target_position;
    double position;
  private:
    void PID();
    
    double prev_error;
    double power;
    double error;
    double integral_sum;
    
};
