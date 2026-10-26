#pragma once
#include "main.h"
#include "claw.hpp"
class Claw{
    public:
    Claw();
        
        bool read_claw_pos(); // Returns true if the claw is open, false if closed
        
        bool read_wrist_pos(); // Returns true if the wrist is down, false if in regular position
        void use_claw();
        void use_wrist();
    private:
        bool claw_position;
        bool wrist_position;
};