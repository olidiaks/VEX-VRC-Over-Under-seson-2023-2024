#include "main.h"
#include <cstdio>

int printStatusOnControllerIterator = 0;

void printStatusOnController() {
  printf("%d\n", printStatusOnControllerIterator);
  printStatusOnControllerIterator ++;
  if (printStatusOnControllerIterator > 10000) {
    printStatusOnControllerIterator = 0;
    controller.print(3, 0, "%d | %d %d %d %d | %d %d", speedPrecent,
                     leftFrontDiveTrainMotor.get_temperature(),
                     leftBackDiveTrainMotor.get_temperature(),
                     rightFrontDiveTrainMotor.get_temperature(),
                     rightBackDiveTrainMotor.get_temperature(),
                     launcherAMotor.get_temperature(),
                     launcherBMotor.get_temperature());
  }
}
