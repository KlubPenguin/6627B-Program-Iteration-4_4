#include "ios.hpp" 





/**
* ASSIGNS WING PORTS DIRECTLY
*/
pros::ADIDigitalOut frontLeftWing(FRONT_LEFT_WING_PORT);
pros::ADIDigitalOut frontRightWing(FRONT_RIGHT_WING_PORT);
pros::ADIDigitalOut backLeftWing(BACK_LEFT_WING_PORT);
pros::ADIDigitalOut backRightWing(BACK_RIGHT_WING_PORT);


/**
* SETS UP POINTERS FOR A DELAYED WING EXECUTION
*/
struct DelayParams 
{
    int delay;
    pros::ADIDigitalOut* wing;
};

/**
* SETS UP POINTERS FOR TWO DELAYED WING EXECUTIONS
*/
struct DoubleDelayParams 
{
    int delay;
    pros::ADIDigitalOut* wing1;
    pros::ADIDigitalOut* wing2;
};


/**
* TASK FUNCTION FOR PUTTING THE WING OUT ON A DELAY
*/
void delayWingOut(void* parameters) 
{
    DelayParams* params = static_cast<DelayParams*>(parameters);
    Clock wingClock(DELAY_TIME);
    while (wingClock.getTime() < params->delay) 
    {
        wingClock.delay();
        pros::delay(DELAY_TIME);
    }
    params->wing->set_value(true);
}

/**
* TASK FUNCTION FOR PUTTING TWO WINGS OUT ON A DELAY
*/
void doubleDelayWingOut(void* parameters) 
{
    DoubleDelayParams* params = static_cast<DoubleDelayParams*>(parameters);
    Clock wingClock(DELAY_TIME);
    while (wingClock.getTime() < params->delay) 
    {
        wingClock.delay();
        pros::delay(DELAY_TIME);
    }
    params->wing1->set_value(true);
    params->wing1->set_value(true);
}

/**
* DELAY TIME IN MS AND SPECIFIC WING TO BE OPENED
*/
void delayOpen(int delay, pros::ADIDigitalOut& wing)
{
    DelayParams DelayParams{delay, &wing};
    pros::Task delayWingTask([](void* params) { delayWingOut(params); }, &DelayParams, "DelayWingTask");
}

/**
* OPENS WING WITH WING PARAMETER
*/
void open(pros::ADIDigitalOut& wing)
{
    wing.set_value(true);
}

/**
* TASK FUNCTION FOR PUTTING THE WING IN ON A DELAY
*/
void delayWingIn(void* parameters) {
    DelayParams* params = static_cast<DelayParams*>(parameters);
    Clock wingClock(DELAY_TIME);
    while (wingClock.getTime() < params->delay) 
    {
        wingClock.delay();
        pros::delay(DELAY_TIME);
    }
    params->wing->set_value(false);
}

/**
* TASK FUNCTION FOR PUTTING TWO WINGS IN ON A DELAY
*/
void doubleDelayWingIn(void* parameters) 
{
    DoubleDelayParams* params = static_cast<DoubleDelayParams*>(parameters);
    Clock wingClock(DELAY_TIME);
    while (wingClock.getTime() < params->delay) 
    {
        wingClock.delay();
        pros::delay(DELAY_TIME);
    }
    params->wing1->set_value(false);
    params->wing2->set_value(false);
}

/**
* DELAY TIME IN MS AND SPECIFIC WING TO BE CLOSED
*/
void delayClose(int delay, pros::ADIDigitalOut& wing) 
{
    DelayParams DelayParams{delay, &wing};
    pros::Task delayWingTask([](void* params) { delayWingIn(params); }, &DelayParams, "DelayWingTask");
}

/**
* CLOSES WING WITH PARAMETERS
*/
void close(pros::ADIDigitalOut& wing)
{
    wing.set_value(false);
}


/**
* OPENS FRONT WINGS
*/
void frontWingsOpen()
{
    frontLeftWing.set_value(true);
    frontRightWing.set_value(true);
}

/**
* CLOSES FRONT WINGS
*/
void frontWingsClose()
{
    frontLeftWing.set_value(false);
    frontRightWing.set_value(false);
}

/**
* OPENS BACK WINGS
*/
void backWingsOpen()
{
    backLeftWing.set_value(true);
    backRightWing.set_value(true);
}

/**
* CLOSES BACK WINGS
*/
void backWingsClose()
{
    backLeftWing.set_value(false);
    backRightWing.set_value(false);
}


/**
* OPENS WINGS ON FRONT OR BACK WITH A DELAY
*/
void delayOpen(std::string face, int delay)
{
    if(face == "front")
    {
    DoubleDelayParams DoubleDelayParams{delay, &frontLeftWing, &frontRightWing};
    pros::Task delayWingTask([](void* params) { doubleDelayWingOut(params); }, &DoubleDelayParams, "DelayWingTask");
    }
    else if(face == "back")
    {
    DoubleDelayParams DoubleDelayParams{delay, &backLeftWing, &backRightWing};
    pros::Task delayWingTask([](void* params) { doubleDelayWingOut(params); }, &DoubleDelayParams, "DelayWingTask");
    }
}

/**
* CLOSES WINGS ON FRONT OR BACK WITH A DELAY
*/
void delayClose(std::string face, int delay)
{
    if(face == "front")
    {
    DoubleDelayParams DoubleDelayParams{delay, &frontLeftWing, &frontRightWing};
    pros::Task delayWingTask([](void* params) { doubleDelayWingIn(params); }, &DoubleDelayParams, "DelayWingTask");
    }
    else if(face == "back")
    {
    DoubleDelayParams DoubleDelayParams{delay, &backLeftWing, &backRightWing};
    pros::Task delayWingTask([](void* params) { doubleDelayWingIn(params); }, &DoubleDelayParams, "DelayWingTask");
    }
}


bool frontWingLock = 0;
bool frontWingMode = 0;
bool backWingMode = 0;
bool backWingLock = 0;
void wingsFXN()
{

if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && (frontWingLock) == 0 && (frontWingMode == 0)){
frontWingMode = 1;
frontWingsOpen();
} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && (frontWingLock == 0) && (frontWingMode == 1)){
frontWingMode = 0;
frontWingsClose();
}

if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
frontWingLock = 1;
} else{
frontWingLock = 0;
}



//BACK WING 

if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && (backWingLock) == 0 && (backWingMode == 0)){
backWingMode = 1;
backWingsOpen();
} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && (backWingLock == 0) && (backWingMode == 1)){
backWingMode = 0;
backWingsClose();
}

if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
backWingLock = 1;
} else{
backWingLock = 0;
}

}