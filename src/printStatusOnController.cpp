#include "main.h"
#include <cstdio>
#include <sstream>
#include <string>

int printStatusOnControllerIterator = 0;

void printStatusOnController() {
  printf("%d\n", printStatusOnControllerIterator);
  printStatusOnControllerIterator++;
  if (printStatusOnControllerIterator > 100) {
    std::string output = "";
    std::stringstream ss;
    ss << speedPrecent << "|" << leftFrontDiveTrainMotor.get_temperature()
       << leftBackDiveTrainMotor.get_temperature()
       << rightFrontDiveTrainMotor.get_temperature()
       << rightBackDiveTrainMotor.get_temperature()
       << launcherAMotor.get_temperature() << "|"
       << launcherBMotor.get_temperature();

    ss >> output;
    controller.set_text(3, 1, output);
    printStatusOnControllerIterator = 0;
  }
}
