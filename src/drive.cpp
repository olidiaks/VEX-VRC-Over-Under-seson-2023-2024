#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include <cmath>
#include <cstdlib>
#include <set>

int speedPrecent = 100;

void setDriveTrain(const int leftMotors, const int rightMotors) {
  leftFrontDiveTrainMotor.move_voltage(leftMotors);
  leftBackDiveTrainMotor.move_voltage(leftMotors);
  rightFrontDiveTrainMotor.move_voltage(rightMotors);
  rightBackDiveTrainMotor.move_voltage(rightMotors);
}

void setMotorsToDriveFromControler(const int speedPrecent) {
  int leftSpeed = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightSpeed = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

  if (-10 < leftSpeed && leftSpeed < 10)
    leftSpeed = 0;
  if (-10 < rightSpeed && rightSpeed < 10)
    rightSpeed = 0;
  leftSpeed = leftSpeed * 12000 * speedPrecent / 100 / 127;
  rightSpeed = rightSpeed * 12000 * speedPrecent / 100 / 127;

  setDriveTrain(leftSpeed, rightSpeed);
}

void changeSpeedOfDriveTraind(int *pSpeedPrecent) {
  *pSpeedPrecent -=
      5 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) -
           controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT));
}

void resetDriveTrainEncoders() {
  leftFrontDiveTrainMotor.tare_position();
  leftBackDiveTrainMotor.tare_position();
  rightFrontDiveTrainMotor.tare_position();
  rightBackDiveTrainMotor.tare_position();
}

double avgDistanceFromDriveTrainEncoders() {
  return (leftFrontDiveTrainMotor.get_position() +
          leftBackDiveTrainMotor.get_position() +
          rightFrontDiveTrainMotor.get_position() +
          rightBackDiveTrainMotor.get_position()) /
         4;
}

void moveRobot(const int distance, const int voltage) {
  const int direction = abs(distance) / distance;

  resetDriveTrainEncoders();
  inertial.tare();

  while (fabs(avgDistanceFromDriveTrainEncoders()) < abs(distance)) {
    setDriveTrain(voltage * direction - inertial.get_rotation() * 200,
                  voltage * direction + inertial.get_rotation() * 200);
    pros::delay(10);
  }

  setDriveTrain(-10 * direction, -10 * direction);
  pros::delay(50);

  setDriveTrain(0, 0);
}

void turnRobot(const int degress, const int voltage){
  int direction = abs(degress) / degress;
  inertial.tare();
  setDriveTrain(voltage * direction, -voltage * direction);
  while (fabs(inertial.get_rotation()) < abs(degress) - 50) {
    pros::delay(10);
  }

  setDriveTrain(0,0);

  pros::delay(100);

  direction = fabs(inertial.get_rotation()) - abs(degress) > 0 ? -direction : direction;

  while (fabs(fabs(inertial.get_rotation()) - abs(degress)) > 5) {
    setDriveTrain(0.5 * voltage * direction, -0.5 * voltage * direction);
  }

  setDriveTrain(0,0);



}
