#pragma once // Prev

#include "main.h"
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

  private:
    
    void PID();

    
    int location;
    double target_position;
    double position;
    double prev_error;
    double power;
    double error;
    double integral_sum;

    // Constants (Tune these for your specific robot!)
    const double kp = 0.8;
    const double ki = 0.0;
    const double kd = 0.1;
};
