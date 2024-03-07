#include "main.h"
#include <fstream>

extern const int autonomusStream[];

void Autonomus::readAutonomusStream() {
  const int *pAutonomusStream = autonomusStream;
  for (int i = 0; sizeof(autonomusStream) > i; i += 6) {
    setDriveTrain(*(pAutonomusStream + i), *(pAutonomusStream + 1 + i));
    setTwoMotorsVoltage(*(pAutonomusStream + 2 + i), launcherAMotor,
                        launcherBMotor);
    setTwoMotorsVoltage(*(pAutonomusStream + 3 + i), leftTriaballGraberMotor,
                        rightTriaballGraberMotor);
    leftAirSystemHandler(false, *(pAutonomusStream + 4 + i));
    rightAirSystemHandler(false, *(pAutonomusStream + 5 + i));
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
  if (counter > 3) {
    std::ofstream ofs("/usd/autonomusStream.hpp", std::ios::app);
    ofs << leftFrontDiveTrainMotor.get_voltage() << ",\t"
        << rightFrontDiveTrainMotor.get_voltage() << ",\t"
        << launcherAMotor.get_voltage() << ",\t"
        << rightTriaballGraberMotor.get_voltage() << ",\t" << isLeftOpen
        << ",\t" << isRightOpen << ",\n";
    ofs.close();
  }
}
