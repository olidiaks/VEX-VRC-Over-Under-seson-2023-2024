#include "main.h"
#include <cstdio>

void twoDigitalButtonsTwoMotorsHandler(
    const pros::controller_digital_e_t buttonPositive,
    const pros::controller_digital_e_t buttonNegative, const pros::Motor motorA,
    pros::Motor motorB, const int voltageMultiplayer) {
  const int power = voltageMultiplayer * (controller.get_digital(buttonPositive) - controller.get_digital(buttonNegative));
  motorA.move_voltage(power);
  motorB.move_voltage(power);
}

void setTwoMotorsVoltage(int voltage, const pros::Motor motorA,
                         pros::Motor motorB) {
  motorA.move_voltage(voltage);
  motorB.move_voltage(voltage);
}
