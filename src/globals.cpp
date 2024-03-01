#include "main.h"
#include "pros/motors.h"
// Decorate motors.
extern pros::Motor leftFrontDiveTrain(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
extern pros::Motor rightFrontDiveTrain;
extern pros::Motor leftBackDiveTrain;
extern pros::Motor rightBackDiveTrain;
extern pros::Motor launcherA;
extern pros::Motor launcherB;
extern pros::Motor triaballGraberA;
extern pros::Motor triaballGraberB;

//Controler
pros::Controller master(pros::E_CONTROLLER_MASTER);
