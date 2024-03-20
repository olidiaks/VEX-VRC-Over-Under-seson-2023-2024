#include "main.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include <cmath>
#include <fstream>

extern const double autonomusStream[];
const double *pAutonomusStream = autonomusStream;

void Autonomus::readAutonomusStream() {
  inertial.reset();
  while (inertial.is_calibrating())
    asm("nop");

  controller.rumble("..");
  for (int i = 0; sizeof(autonomusStream) > i; i += 9) {
    /* while (fabs(inertial.get_rotation() - *(pAutonomusStream + i)) > 9) {
      const float errorInHeading =
          inertial.get_rotation() - *(pAutonomusStream + i);
      const float speedFormotors = errorInHeading * 400;
      setDriveTrain(-speedFormotors, speedFormotors);
    } */
    // setDriveTrain(*(pAutonomusStream + i + 1), *(pAutonomusStream + 2 + i));
    setTwoMotorsVoltage(*(pAutonomusStream + 3 + i), launcherAMotor,
                        launcherBMotor);
    setTwoMotorsVoltage(*(pAutonomusStream + 4 + i), leftTriaballGraberMotor,
                        rightTriaballGraberMotor);
    leftAirSystemHandler(false, *(pAutonomusStream + 5 + i));
    rightAirSystemHandler(false, *(pAutonomusStream + 6 + i));

    do {
      setDriveTrain(500 * (*(pAutonomusStream + i + 7) -
                           leftFrontDiveTrainMotor.get_position() -
                           leftBackDiveTrainMotor.get_position()),
                    500 * (*(pAutonomusStream + i + 8) -
                           rightFrontDiveTrainMotor.get_position() -
                           rightBackDiveTrainMotor.get_position()));
      pros::delay(10);
    } while (fabs(*(pAutonomusStream + i + 7) -
                  leftFrontDiveTrainMotor.get_position() -
                  leftBackDiveTrainMotor.get_position()) > 3 &&
             fabs(*(pAutonomusStream + i + 8) -
                  rightFrontDiveTrainMotor.get_position() -
                  rightBackDiveTrainMotor.get_position()) > 3);
  }
}

bool Autonomus::moveMotor(const pros::Motor motorFront,
                          const pros::Motor motorBack, const int i,
                          const int motorId) {

  return fabs(*(pAutonomusStream + i + 7) -
              leftFrontDiveTrainMotor.get_position() -
              leftBackDiveTrainMotor.get_position()) > 3;
}

Autonomus::Autonomus() {
  std::ofstream ofs("/usd/autonomusStream.hpp", std::ios::trunc);
  ofs << "#include \"main.h\"\n";
  ofs << "static const double autonomusStream[] = {\n";
  ofs.close();
}

extern bool isLeftOpen;
extern bool isRightOpen;

void Autonomus::writeAutonomusStream() {
  std::ofstream ofs("/usd/autonomusStream.hpp", std::ios::app);
  ofs << int(inertial.get_rotation()) << ", \t"
      << leftFrontDiveTrainMotor.get_voltage() << ",\t"
      << rightFrontDiveTrainMotor.get_voltage() << ",\t"
      << launcherAMotor.get_voltage() << ",\t"
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
