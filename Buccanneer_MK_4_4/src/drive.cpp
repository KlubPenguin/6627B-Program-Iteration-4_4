#include "ios.hpp"




pros::Motor frontLeft(FRONT_LEFT_MOTOR_PORT);
pros::Motor midLeft(MID_LEFT_MOTOR_PORT);
pros::Motor backLeft(BACK_LEFT_MOTOR_PORT);

pros::Motor frontRight(FRONT_RIGHT_MOTOR_PORT);
pros::Motor midRight(MID_RIGHT_MOTOR_PORT);
pros::Motor backRight(BACK_RIGHT_MOTOR_PORT);

pros::Rotation latRotation(LAT_ROTATION_PORT, REVERSED_LATERAL);
pros::Rotation horizontalRotation(HORIZONTAL_ROTATION_PORT, REVERSED_HORIZONTAL);

pros::IMU imu(IMU_PORT);

int latVolts;
int turnVolts;

double rightSpeed;
double leftSpeed;
double maxDrive;

std::string brakeMode = "coast";
bool brakeLock = false;


void driveFXN(){


if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B) && !brakeLock && (brakeMode == "coast"))
{
   brakeMode = "coast";
   brakeLock = true;
}
else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B) && !brakeLock && (brakeMode == "hold"))
{
   brakeMode = "hold";
   brakeLock = true;
}

if(brakeMode == "coast")
{
   frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
   midLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
   backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
   frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
   midRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
   backRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}
else if (brakeMode == "hold")
{
   frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
   midLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
   backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
   frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
   midRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
   backRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);  
}

if(!master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
{
   brakeLock = false;
}

if((abs(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) > 12) && (abs(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) < 12)){
latVolts = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
turnVolts = 0;
} else if ((abs(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) > 12) && (abs(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) > 12)){
latVolts = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
turnVolts = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
} else if((abs(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) < 12) && (abs(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) > 12)){
turnVolts = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
latVolts = 0;
} else{
turnVolts = 0;
latVolts = 0;
}

rightSpeed = latVolts - turnVolts;
leftSpeed = latVolts + turnVolts;
maxDrive = std::max(abs(rightSpeed), abs(leftSpeed))/127;


if(maxDrive > 127){
frontLeft = leftSpeed/maxDrive;
midLeft = leftSpeed/maxDrive;
backLeft = leftSpeed/maxDrive;
frontRight = rightSpeed/maxDrive;
midRight = rightSpeed/maxDrive;
backRight = rightSpeed/maxDrive;

} else if(abs(rightSpeed) > 12 || abs(leftSpeed) > 12){
frontLeft = leftSpeed;
midLeft = leftSpeed;
backLeft = leftSpeed;
frontRight = rightSpeed;
midRight = rightSpeed;
backRight = rightSpeed;
} else{
   frontLeft.brake();
   midLeft.brake();
   backLeft.brake();
   frontRight.brake();
   midRight.brake();
   backRight.brake();

}
}

void lemlibDrive()
{
       // takes each side's drive power in the range [-127, 127] and a curve gain
    chassis.tank(
        // left drive power
        master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
        // right drive power
        master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y),
        // drive curve gain to enable greater control of the robot.
        15);
}

void chassisDisplay()
{
   pros::lcd::print(1, "Left Volts: %d", returnVolts(leftSpeed));

   pros::lcd::print(2, "Right Volts: %d", returnVolts(rightSpeed));


}
