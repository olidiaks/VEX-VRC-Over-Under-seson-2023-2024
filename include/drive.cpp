#include "main.h"

void setDriveTrain(const int leftMotors, const int rightMotors){
	leftFrontDiveTrainMotor.move_voltage(leftMotors);
	leftBackDiveTrainMotor.move_voltage(leftMotors);
	rightFrontDiveTrainMotor.move_voltage(rightMotors);
	rightBackDiveTrainMotor.move_voltage(rightMotors);
}
