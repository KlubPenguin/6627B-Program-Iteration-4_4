#include "autons.hpp"
#include "fxns.hpp"


void far6Ball_V1()
{
    //ROBOT IS FACING HANG BAR
    chassis.setPose(131, 98.2, -180);


    //GET HANGING BALL
    intakeIn();

    chassis.moveToPose(131, 89, -180, 1000);
    chassis.waitUntilDone();

    intakeStop();

    //MOVE TO LOADING BALL
    chassis.moveToPose(131, 121, -180, 1000, {false});
    chassis.waitUntilDone();

    open(backLeftWing);

    chassis.moveToPose(117, 134, -225, 1000, {false});
    chassis.waitUntilDone();

    close(backLeftWing);


    //PUSH LOADING BALL AND ALLY BALL IN GOAL
    chassis.moveToPose(96.5, 139.4, -270, 1000, {false});
    chassis.waitUntilDone();

    //RETREAT FROM GOAL
    chassis.moveToPose(106.5, 139.4, -270, 1000);
    chassis.waitUntilDone();

    //PUSH HANG BALL IN GOAL
    chassis.turnTo(96.5, 0, 300);
    chassis.turnTo(96.5, 142, 600);
    chassis.waitUntilDone();

    intakeOut();


    chassis.moveToPose(87.5, 142, -90, 500);
    chassis.waitUntilDone();


    pros::delay(500);
    intakeStop();

    //HEAD FOR SAFE BALL (BALL 4)
    chassis.moveToPose(120, 142, -90, 1000, {false});
    chassis.waitUntilDone();  

    chassis.turnTo(100, 96, 700);
        
    intakeIn();
//
    chassis.moveToPose(100, 96, -162, 2000);
    chassis.waitUntilDone();  

    intakeStop();

    //SEND SAFE BALL (4TH BALL) TO GOAL
    /*
    chassis.turnTo(92, 103, 4000);
    chassis.waitUntilDone();  

    intakeIn();
    */


}