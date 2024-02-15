#include "ios.hpp"

   Clock cataClock(DELAY_TIME);
   pros::Motor bigCatapult(BIG_CATAPULT_PORT);
   pros::Motor smallCatapult(SMALL_CATAPULT_PORT);
   pros::Rotation cataRotation(CATAPULT_ROTATION_PORT);
   pros::Distance cataDistance(DISTANCE_PORT);


  int cataStart = 0;
  bool autoLock = 0;
  bool semiAutoLock = 0;
  bool setFireLock = 0;
  bool cataShots = 0;
  bool cataFired = 0;
  std::string catapultMode = "loading";

bool isAtPosition()
{
  if(NORMAL_ROTATION)
  {
    if((cataRotation.get_angle()/100 > PRIME_POSITION))
    {
      return false;
    } 
    else
    {
      return true;
    }
  }
  else
  {
      if((cataRotation.get_angle()/100 < PRIME_POSITION))
      {
        return false;
      }
      else
      {
        return true;
      }
  }
}

void catapultStart()
{

  cataStart = 0;
    
    if(!isAtPosition()){
    catapultMode = "resetting";
    }else{

    catapultMode = "loading";
    cataStart = 1;
    }
    smallCatapult.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    bigCatapult.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

}

void catapultFXN(){
    if(cataStart == 0){
    /*
    if(isAtPosition){
    catapultMode = "resetting";
    }else{
      }*/
    catapultMode = "loading";
    cataStart = 1;
    } else if (cataStart == 1){
    if ((catapultMode == "resetting")  && (!isAtPosition) && (cataClock.getTime() > FIRING_PERIOD)) {
    catapultMode = "loading";
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && (autoLock == 0)){
    cataStart = 2;
    autoLock = 1;
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && (semiAutoLock == 0)){
    cataStart = 3;
    semiAutoLock = 1;
    catapultMode = "waiting";
    } 
    /* else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) && (setFireLock == 0)){
    cataStart = 5;
    setFireLock = 1;
    catapultMode = "autofire";
    cataShots = 1;
    cataFired = 0;
    }  */ 

    } else if(cataStart == 2){
    catapultMode = "autofire";
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && (autoLock == 0)){
    cataStart = 0;
    autoLock = 1;
    }

    } else if (cataStart == 3){
    if ((catapultMode == "distancefire") && (isAtPosition()) &&  (cataClock.getTime() > FIRING_PERIOD)){
    cataClock.reset();
    catapultMode = "waiting";

    } else if ((catapultMode == "waiting") && (cataDistance.get() < DETECTION_RANGE)){
    catapultMode = "distancefire";
    cataClock.reset();
    } 



    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && (semiAutoLock == 0)){
    cataStart = 0;
    semiAutoLock = 1;
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && (semiAutoLock == 0)){
    cataStart = 0;
    semiAutoLock = 1;
    }

    }/* else if (cataStart == 5){

    if(cataShots > cataFired){
    if((cataClock.getTime() >= 300) && (cataRotation.get_angle()/100) >= 115){
    cataClock.getTime() = 0;
    cataFired++;
    } 

    catapultMode = "setfire";


    } else {
    cataStart = 0;
    catapultMode = "waiting";  
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && (setFireLock == 0)){
    cataStart = 0;
    setFireLock = 1;
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) && (setFireLock == 0)){
    cataShots++;
    setFireLock = 1;
    } 


    } */





    
    //SCRAPPED CATA FXN
    /*else if (cataStart == 4){
    if ((catapultMode == "distancefire") && ( 230 > (cataRotation.get_angle()/100)) &&  (cataClock.getTime() > 400)){
    cataClock.getTime() = 0;
    catapultMode = "waiting";

    } else if ((catapultMode == "waiting") && (cataClock.getTime() > 3000)){
    cataStart = 0;
    } 
    
    } */

    if(!master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
    autoLock = 0;
    }


    if(!master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
    semiAutoLock = 0;
    }


    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
    cataClock.reset();
    }



    if(!master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && !master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
    setFireLock = 0;
    }


    if(catapultMode == "resetting"){
    bigCatapult = 90;
    smallCatapult = 90;
    } else if (catapultMode == "loading" || catapultMode == "blocking" || catapultMode == "waiting"){
    bigCatapult.brake();
    smallCatapult.brake();
    } else if (catapultMode == "lowering"){
    bigCatapult = 89;
    smallCatapult = 89;
    } else if (catapultMode == "setfire"  || catapultMode == "distancefire"){
    bigCatapult = 127;
    smallCatapult = 127;
    } else if (catapultMode == "autofire"){
    bigCatapult = returnEightBit(AUTOFIRE_SPEED);
    smallCatapult = returnEightBit(AUTOFIRE_SPEED);
    } 

    cataClock.delay();
}

double cataTemp()
{
  double cataCelsius = std::max(bigCatapult.get_temperature(), smallCatapult.get_temperature());
  return static_cast<double>(cataCelsius * 1.8 + 32);
}

void catapultDisplay()
{

    pros::lcd::print(1, "Catapult Temp: %f", cataTemp());

    pros::lcd::print(2,"Catapult Shots: %d",  cataShots);

    pros::lcd::print(3, "Cata Angle %d", cataRotation.get_angle()/100);
    
		pros::lcd::print(4, "Distance: %d", cataDistance.get()); 

		pros::lcd::print(5, "Mode: %s", catapultMode);      

    pros::lcd::print(7, "Cata Clock: %d", cataClock.getTime());

}