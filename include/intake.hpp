#pragma once
#include "main.h"
#include "intake.hpp"
class Intake{
    public:
        Intake();
        void initialize(void);
        
        void intake(int vel); 

     
        void outtake(int vel);
        void stop(void);
        
        int read_velocity(void);
    private:
        int velocity;
};