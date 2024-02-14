#include "fxns.hpp"
#include "ios.hpp"

int prevClicks = 0;
bool displayLock = 0;
int displayCount = 0;
const int TOTAL_DISPLAYS = 2;
Clock displayClock(DELAY_TIME);

void swapDisplay()
{
    displayCount++;
    if(displayCount == TOTAL_DISPLAYS)
    {
        displayCount = 0;
    }
}

void displayFXN()
{
    pros::lcd::clear_line(0);
    pros::lcd::clear_line(1);
    pros::lcd::clear_line(2);
    pros::lcd::clear_line(3);
    pros::lcd::clear_line(4);
    pros::lcd::clear_line(5);
    pros::lcd::clear_line(6);
    pros::lcd::clear_line(7);

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) && !displayLock)
    {
        prevClicks++;
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
    {
        displayLock = 1;
    }
    else
    {
        displayLock = 0;
    }

    if(displayClock.getTime() > DOUBLE_CLICK_DELAY)
    {
        displayClock.reset();
    }

    if(prevClicks == 2)
    {
        swapDisplay();
        prevClicks = 0;
    }

    if(displayCount == 0)
    {
        odomDisplay();
    }
    else if(displayCount == 1)
    {
        catapultDisplay();
    }

    displayClock.delay();
}

