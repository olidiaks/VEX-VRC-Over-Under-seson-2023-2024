#include "main.h"
// Decorate motors.
pros::Motor leftFrontDiveTrainMotor(-8);
pros::Motor rightFrontDiveTrainMotor(5);
pros::Motor leftBackDiveTrainMotor(-9);
pros::Motor rightBackDiveTrainMotor(4);
pros::Motor launcherAMotor(-6);
pros::Motor launcherBMotor(16);
pros::Motor leftTriaballGraberMotor(10);
pros::Motor rightTriaballGraberMotor(1);

//Triple ports
pros::adi::DigitalOut leftWing(2);
pros::adi::DigitalOut rightWing(3);

// Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);
