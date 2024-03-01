#include "main.h"

void setDriveTrain(const int leftMotors, const int rightMotors){
	leftFrontDiveTrainMotor.move_voltage(leftMotors);
	leftBackDiveTrainMotor.move_voltage(leftMotors);
	rightFrontDiveTrainMotor.move_voltage(rightMotors);
	rightBackDiveTrainMotor.move_voltage(rightMotors);
}

void setMotorsToDriveFromControler(const int speedPrecent){
	int leftSpeed = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int rightSpeed = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

	if (-10 < leftSpeed && leftSpeed < 10) leftSpeed = 0;
	if (-10 < rightSpeed && rightSpeed < 10) rightSpeed = 0;
	leftSpeed = leftSpeed * speedPrecent / 100;
	rightSpeed = rightSpeed * speedPrecent / 100;
	
	setDriveTrain(leftSpeed, rightSpeed);
}
