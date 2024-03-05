#include "main.h"
#include "pros/rtos.hpp"
#include <cstdio>

void twoDigitalButtonsTwoMotorsHandler(
    const pros::controller_digital_e_t buttonPositive,
    const pros::controller_digital_e_t buttonNegative, const pros::Motor motorA,
    pros::Motor motorB, const int voltageMultiplayer) {
  printf("two buttons function is called\n");
  const int power = voltageMultiplayer * (controller.get_digital(buttonPositive) - controller.get_digital(buttonNegative));
  motorA.move_voltage(power);
  motorB.move_voltage(power);
}

void setTwoMotorsVoltage(int voltage, const pros::Motor motorA,
                         pros::Motor motorB) {
  printf("two motors set voltage is called\n");
  motorA.move_voltage(voltage);
  motorB.move_voltage(voltage);
}
