#include "main.h"
#include "pros/llemu.hpp"

void printTemperatureOfMotrs() {

  pros::lcd::print(2, "Graber l %.0f r %.0f",
                   leftTriaballGraberMotor.get_temperature(),
                   rightTriaballGraberMotor.get_temperature());
  pros::lcd::print(3, "Launcher %.0f %.0f", launcherAMotor.get_temperature(),
                   launcherBMotor.get_temperature());
  pros::lcd::print(4, "Drive train: lf %.0f lb %.0f rf %.0f rb %.0f",
                   leftFrontDiveTrainMotor.get_temperature(),
                   leftBackDiveTrainMotor.get_temperature(),
                   rightFrontDiveTrainMotor.get_temperature(),
                   rightBackDiveTrainMotor.get_temperature());
}
