#include "ios.hpp"





int intakeSpeed = 0;


pros::Motor intake(INTAKE_PORT);

void intakeFXN(){
if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
intakeSpeed = -1;
//master.print(1, 0, "Intake: Outaking"); 
} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
intakeSpeed = 1;
//master.print(1, 0, "Intake: Intaking"); 
} else {
intakeSpeed = 0;
//master.print(2, 0, "Intake: Coasting"); 
}
intake = 127 * intakeSpeed;
}

void intakeIn()
{
    intake = 127;
}

void intakeStop()
{
    intake = 0;
}

void intakeOut()
{
    intake = -127;
}