#include "main.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>

extern const int autonomusStream[];

void Autonomus::readAutonomusStream() {
  inertial.reset();
  while (inertial.is_calibrating()) {
    asm("nop");
  }
  controller.rumble("..");
  const int *pAutonomusStream = autonomusStream;
  for (int i = 0; sizeof(autonomusStream) > i; i += 7) {
    while (inertial.get_heading() - *(pAutonomusStream + i) > 9 ||inertial.get_heading() - *(pAutonomusStream + i) < -9) {
      const float errorInHeading =
          inertial.get_heading() - *(pAutonomusStream + i);
      const float speedFormotors =
          (errorInHeading > 180 ? -errorInHeading / 2 : errorInHeading) * 320;
      setDriveTrain(-speedFormotors, speedFormotors);
      printf("error in heding: %f\nspeedForMotors: %f\n", errorInHeading, speedFormotors);
    }
    setDriveTrain(*(pAutonomusStream + i + 1), *(pAutonomusStream + 2 + i));
    setTwoMotorsVoltage(*(pAutonomusStream + 3 + i), launcherAMotor,
                        launcherBMotor);
    setTwoMotorsVoltage(*(pAutonomusStream + 4 + i), leftTriaballGraberMotor,
                        rightTriaballGraberMotor);
    leftAirSystemHandler(false, *(pAutonomusStream + 5 + i));
    rightAirSystemHandler(false, *(pAutonomusStream + 6 + i));
    pros::delay(10);
  }
}

Autonomus::Autonomus() {
  std::ofstream ofs("/usd/autonomusStream.hpp", std::ios::trunc);
  ofs << "#include \"main.h\"\n";
  ofs << "static const int autonomusStream[] = {\n";
  ofs.close();
}

extern bool isLeftOpen;
extern bool isRightOpen;

void Autonomus::writeAutonomusStream() {
  std::ofstream ofs("/usd/autonomusStream.hpp", std::ios::app);
  ofs << int (inertial.get_heading()) << ", \t"
      << leftFrontDiveTrainMotor.get_voltage() << ",\t"
      << rightFrontDiveTrainMotor.get_voltage() << ",\t"
      << launcherAMotor.get_voltage() << ",\t"
      << rightTriaballGraberMotor.get_voltage() << ",\t" << isLeftOpen << ",\t"
      << isRightOpen << ",\n";
  ofs.close();
}
