#include "main.h"

void twoDigitalButtonsTwoMotorsHandler(
    const pros::controller_digital_e_t buttonPositive,
    const pros::controller_digital_e_t buttonNegative, const pros::Motor motorA,
    pros::Motor motorB, const float voltageMultiplayer = 1);

void setTwoMotorsVoltage(int voltage, const pros::Motor motorA,
                         pros::Motor motorB);

class oneToggleButtonsTwoMotorsHandler : private ToggleButton{

private:
  pros::Motor* motorA;
  pros::Motor* motorB;
  float voltageMultiplayer;
  bool areMotorsSpining = false;

public:
  oneToggleButtonsTwoMotorsHandler(const pros::controller_digital_e_t button,
                                   pros::Motor* motorA, pros::Motor* motorB,
                                   const float voltageMultiplayer = 1);
  void updateMotors();
};
