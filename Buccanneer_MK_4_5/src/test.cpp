#include "autons.hpp"


void test()
{
    /*
    Pos pos(144, 78, 0);
	chassis.setPose(pos.newX(), pos.newY(), pos.newTheta());


    pos.move(12);
    chassis.moveToPose(pos.newX(), pos.newY(), 1000, 95);
    pos.align();
    */
    /*
 intakeIn();
 pros::delay(500);
 intakeOut();
 pros::delay(500);
 intakeStop();
*/
 frontWingsOpen();
 
 pros::delay(500);

 frontWingsClose();
 
 pros::delay(500);

 backWingsOpen();
 
 pros::delay(500);

 backWingsClose();
 
 pros::delay(500);

 open(backLeftWing);
 open(backRightWing);
 open(frontLeftWing);
 open(frontRightWing);

 pros::delay(500);

 close(backLeftWing);
 close(backRightWing);
 close(frontLeftWing);
 close(frontRightWing);

 pros::delay(500);
 hangUp();

 pros::delay(500);
 hangDown();

}