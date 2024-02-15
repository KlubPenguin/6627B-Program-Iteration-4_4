#include "ios.hpp"



pros::ADIDigitalOut upHang(UP_HANG_PORT);
pros::ADIDigitalOut downHang(DOWN_HANG_PORT);

void hangUp()
{
    downHang.set_value(false);
    upHang.set_value(true);
}

void hangDown()
{
    upHang.set_value(false);
    downHang.set_value(true);
}

void hangDisabled()
{
    if(driveRan && pros::competition::is_disabled)
    {
        hangDown();
    }
}

void hangInitialize()
{
    if(!autonRan && pros::competition::is_disabled)
    {
        hangUp();
    }
}


bool hangMode = 1;
bool hangLock = 0;
void hangFXN()
{
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) && !hangLock && !hangMode)
    {
        hangMode = 1;
        hangDown();
    } 
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) && !hangLock && hangMode)
    {
        hangMode = 0;
        hangUp();
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
    {
        hangLock = 1;
    } 
    else
    {
        hangLock = 0;
    }
}