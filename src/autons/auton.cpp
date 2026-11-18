
#include "main.h"
#include "pros/misc.h"
#include "drive.hpp"
#include "devices.hpp"
#include "config.hpp"
#include "autons_header/auton.hpp"
#include <cmath>
#include <algorithm>
#include "lemlib/api.hpp"

bool tmpflag = false;
void runAuton(){
    chassis.setPose(0, 0, 0);
    
}
void testtune(){
    if(tmpflag == false){
        chassis.turnToHeading(90, 10000);
    }
    else if(tmpflag == true){
        chassis.turnToHeading(0, 10000);
    }
    tmpflag=!tmpflag;
    /*if(tmpflag == false){
        chassis.movetoPose(0,24,0, 10000);
    }
    else if(tmpflag == true){
        chassis.turnToHeading(0,0,0, 10000);
    }*/
}