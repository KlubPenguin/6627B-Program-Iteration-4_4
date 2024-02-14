#include "ios.hpp"


pros::MotorGroup leftMotors({frontLeft, midLeft, backLeft});
pros::MotorGroup rightMotors({frontRight, midRight, backRight});


lemlib::Drivetrain drivetrain {
    &leftMotors, // left drivetrain motors
    &rightMotors, // right drivetrain motors
    TRACK_WIDTH, // track width
    DRIVE_DIAMETER, // wheel diameter
    DRIVE_RPM, // wheel rpm
    100000, //what is chase power
};



lemlib::TrackingWheel lat_tracker(&latRotation, LAT_TRACKING_DIAMETER, PERPENDICULAR_LATERAL_DISTANCE, 1);

lemlib::TrackingWheel horizontal_tracker(&horizontalRotation, HORIZONTAL_TRACKING_DIAMETER, PERPENDICULAR_HORIZONTAL_DISTANCE, 1);



lemlib::OdomSensors sensors {
    &lat_tracker, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    &horizontal_tracker, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &imu // inertial sensor
};

// lateral motion controller
lemlib::ControllerSettings linearController(
    35, // proportional gain (kP)
    3, //ki
    200, // derivative gain (kD)
    3, //winduprange
    1, // small error range, in inches
    100, // small error range timeout, in milliseconds
    3, // large error range, in inches
    100, // large error range timeout, in milliseconds
    20 // maximum acceleration (slew)

);

lemlib::ControllerSettings angularController(
    4, // proportional gain (kP)
    0, //ki
    30, // derivative gain (kD)
    3, //wind up range
    1, // small error range, in degrees
    100, // small error range timeout, in milliseconds
    3, // large error range, in degrees
    500, // large error range timeout, in milliseconds
    0 // maximum acceleration (slew)
);

lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);


void odomDisplay()
{
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
}

void loopOdomDisplay()
{
    while(1)
    {
        odomDisplay();
        pros::delay(DELAY_TIME);
    }
}