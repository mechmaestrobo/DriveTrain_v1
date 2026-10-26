//This is where the claw class is defined
#include "claw.hpp"
#include "main.h"
#include "devices.hpp"
#include "config.hpp"
#include <cmath>
#include <numeric>
Claw::Claw(){

    claw_position = false;
    wrist_position = false;
}
void Claw::use_claw(){
    claw_position = !claw_position;
    claw_piston.set_value(claw_position);
}
void Claw::use_wrist(){
    wrist_position = !wrist_position;
    if(wrist_position == true){
        wristMotor.move_absolute(-100, 100);
    }
    else{
        wristMotor.move_absolute(0, 100);
    }
}
bool Claw::read_claw_pos(){
    return claw_position;
}
bool Claw::read_wrist_pos(){
    return wrist_position;
}
