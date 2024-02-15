#pragma once
#include "api.h"
#include "clock.hpp"
#include "calc.hpp"
#include "lemlib/api.hpp"

#ifndef IOS_PAGE_HPP


   extern pros::Motor frontLeft;
   extern pros::Motor midLeft;
   extern pros::Motor backLeft;
   extern const int FRONT_LEFT_MOTOR_PORT;
   extern const int MID_LEFT_MOTOR_PORT;
   extern const int BACK_LEFT_MOTOR_PORT;

   extern pros::Motor frontRight;
   extern pros::Motor midRight;
   extern pros::Motor backRight;
   extern const int FRONT_RIGHT_MOTOR_PORT;
   extern const int MID_RIGHT_MOTOR_PORT;
   extern const int BACK_RIGHT_MOTOR_PORT;

   extern pros::Rotation latRotation;
   extern pros::Rotation horizontalRotation;
   extern const int LAT_ROTATION_PORT;
   extern const int HORIZONTAL_ROTATION_PORT;
   extern const bool REVERSED_HORIZONTAL;
   extern const bool REVERSED_LATERAL;
   extern const float TRACK_WIDTH;
   extern const float DRIVE_DIAMETER;
   extern const float DRIVE_RPM;
   extern const double HORIZONTAL_TRACKING_DIAMETER;
   extern const double PERPENDICULAR_HORIZONTAL_DISTANCE;
   extern const double PERPENDICULAR_LATERAL_DISTANCE;
   extern const double LAT_TRACKING_DIAMETER;
   extern const int IMU_PORT;
   extern pros::IMU imu;

   extern pros::Motor bigCatapult;
   extern pros::Motor smallCatapult;
   extern pros::Distance cataDistance;
   extern pros::Rotation cataRotation;
   extern const int BIG_CATAPULT_PORT;
   extern const int SMALL_CATAPULT_PORT;
   extern const int DISTANCE_PORT;
   extern const int CATAPULT_ROTATION_PORT;
   extern const int FIRING_PERIOD;
   extern const int DETECTION_RANGE;
   extern const bool NORMAL_ROTATION;
   extern const int PRIME_POSITION;
   extern const int AUTOFIRE_SPEED;

   extern pros::Motor intake;
   extern const int INTAKE_PORT;

   extern lemlib::Chassis chassis;
   extern pros::Controller master; 

   extern pros::ADIDigitalOut frontLeftWing;
   extern pros::ADIDigitalOut frontRightWing;
   extern pros::ADIDigitalOut backLeftWing;
   extern pros::ADIDigitalOut backRightWing;
   extern const char FRONT_LEFT_WING_PORT;
   extern const char FRONT_RIGHT_WING_PORT;
   extern const char BACK_LEFT_WING_PORT;
   extern const char BACK_RIGHT_WING_PORT;
 
   extern pros::ADIDigitalOut upHang;
   extern pros::ADIDigitalOut downHang;
   extern const char UP_HANG_PORT;
   extern const char DOWN_HANG_PORT;

   extern const int DELAY_TIME;
   extern const int DOUBLE_CLICK_DELAY;
   extern Clock cataClock;

   extern bool autonRan;
   extern bool driveRan;

   #endif