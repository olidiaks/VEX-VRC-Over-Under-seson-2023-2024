#include "main.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include <cmath>
#include <fstream>

extern const double autonomusStream[];

void Autonomus::readAutonomusStream() {
  const double *pAutonomusStream = autonomusStream;
  /* inertial.reset();
  while (inertial.is_calibrating())
    asm("nop"); */

  controller.rumble("..");
  for (int i = 0; sizeof(autonomusStream) > i; i += 6) {
    setTwoMotorsVoltage(*(pAutonomusStream + 0 + i), launcherAMotor,
                        launcherBMotor);
    setTwoMotorsVoltage(*(pAutonomusStream + 1 + i), leftTriaballGraberMotor,
                        rightTriaballGraberMotor);
    leftAirSystemHandler(false, *(pAutonomusStream + 2 + i));
    rightAirSystemHandler(false, *(pAutonomusStream + 3 + i));

    do {
      setDriveTrain(500 * (*(pAutonomusStream + i + 4) -
                           leftFrontDiveTrainMotor.get_position() -
                           leftBackDiveTrainMotor.get_position()),
                    500 * (*(pAutonomusStream + i + 5) -
                           rightFrontDiveTrainMotor.get_position() -
                           rightBackDiveTrainMotor.get_position()));
      pros::delay(10);
    } while (fabs(*(pAutonomusStream + i + 4) -
                  leftFrontDiveTrainMotor.get_position() -
                  leftBackDiveTrainMotor.get_position()) > 10 &&
             fabs(*(pAutonomusStream + i + 5) -
                  rightFrontDiveTrainMotor.get_position() -
                  rightBackDiveTrainMotor.get_position()) > 10);
    printTemperatureOfMotrs();
  }
  setDriveTrain(0, 0);
}

Autonomus::Autonomus() {
  std::ofstream ofs("/usd/autonomusStream.hpp", std::ios::trunc);
  ofs << "#include \"main.h\"\n";
  ofs << "static const double autonomusStream[] = {\n";
  ofs.close();
  tareMotors();
}

extern bool isLeftOpen;
extern bool isRightOpen;

void Autonomus::writeAutonomusStream() {
  std::ofstream ofs("/usd/autonomusStream.hpp", std::ios::app);
  ofs << launcherAMotor.get_voltage() << ",\t"
      << rightTriaballGraberMotor.get_voltage() << ",\t" << isLeftOpen << ",\t"
      << isRightOpen << ",\t"
      << leftFrontDiveTrainMotor.get_position() +
             leftBackDiveTrainMotor.get_position()
      << ",\t"
      << rightBackDiveTrainMotor.get_position() +
             rightBackDiveTrainMotor.get_position()
      << ", \n";

  ofs.close();

  pros::delay(10);
}
