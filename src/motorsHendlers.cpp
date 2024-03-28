#include "main.h"

void twoDigitalButtonsTwoMotorsHandler(
    const pros::controller_digital_e_t buttonPositive,
    const pros::controller_digital_e_t buttonNegative, const pros::Motor motorA,
    pros::Motor motorB, const int voltageMultiplayer) {
  const float power =
      voltageMultiplayer * (controller.get_digital(buttonPositive) -
                            controller.get_digital(buttonNegative));
  motorA.move_voltage(power);
  motorB.move_voltage(power);
}

oneToggleButtonsTwoMotorsHandler::oneToggleButtonsTwoMotorsHandler(
    const pros::controller_digital_e_t button, pros::Motor *motorA,
    pros::Motor *motorB, const float voltageMultiplayer) {
  this->motorA = motorA;
  this->motorB = motorB;
  this->voltageMultiplayer = voltageMultiplayer;
}

void oneToggleButtonsTwoMotorsHandler::updateMotors() {
    updateStatus();
  if (getState()) {
    areMotorsSpining = !areMotorsSpining;
    const int voltage = areMotorsSpining * 12000 * voltageMultiplayer;
    motorA->move_voltage(voltage);
    motorB->move_voltage(voltage);
  }
}

void setTwoMotorsVoltage(int voltage, const pros::Motor motorA,
                         pros::Motor motorB) {
  motorA.move_voltage(voltage);
  motorB.move_voltage(voltage);
}
