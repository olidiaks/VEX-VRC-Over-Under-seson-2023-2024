#include "main.h"
#include <cstdlib>
#include <fstream>

extern const int autonomusStream[];

void Autonomus::readAutonomusStream() {
  while (inertial.is_calibrating()) {
    printf("inertail sensor is calibrating\n");
  }
  const int *pAutonomusStream = autonomusStream;
  for (int i = 0; sizeof(autonomusStream) > i; i += 7) {
    while (std::abs(inertial.get_heading() - *(pAutonomusStream + i)) > 5) {
      const float errorInHeading =
           inertial.get_heading() - *(pAutonomusStream + i);
      const float speedFormotors = (errorInHeading > 180 ? errorInHeading / 2 : errorInHeading) * 200;
      setDriveTrain(-errorInHeading, errorInHeading);
      printf("Error in heading: %f\nspeed: %f", errorInHeading, speedFormotors);
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
  counter = 0;
}

extern bool isLeftOpen;
extern bool isRightOpen;

void Autonomus::writeAutonomusStream() {
  counter++;
  if (counter > 100) {
    std::ofstream ofs("/usd/autonomusStream.hpp", std::ios::app);
    ofs << (int)inertial.get_heading() << ", \t"
        << leftFrontDiveTrainMotor.get_voltage() << ",\t"
        << rightFrontDiveTrainMotor.get_voltage() << ",\t"
        << launcherAMotor.get_voltage() << ",\t"
        << rightTriaballGraberMotor.get_voltage() << ",\t" << isLeftOpen
        << ",\t" << isRightOpen << ",\n";
    ofs.close();
  }
}
