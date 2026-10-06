#pragma once
#include "main.h"
#include "intake.hpp"
class Intake{
    public:
        Intake();
        void initialize(void);
         /**
     * @brief Runs the intake
     *Runs the intake at a provided velocity
     * @param vel The velocity to set for the intake motor.(0 - 200 rpm)
     * 
     **/
        void intake(int vel);
        /**
     * @brief Runs the intake backward
     *Runs the intake backward at a provided velocity
     * @param vel The velocity to set for the intake motor.(0 - 200 rpm)
     * 
     **/
        void outtake(int vel);
        void stop(void);
        /**
         * @brief will return velocity.
         * 
         * @return positive means intake, negative means outtake
         */
        int read_velocity(void);
    private:
        int velocity;
};