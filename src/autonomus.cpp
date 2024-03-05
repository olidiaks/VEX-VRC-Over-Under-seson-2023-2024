#include "main.h"
#include <cstdio>
#include <fstream>

static const int autonomusStream[] = {};

void readAutonomusStream() {
  const int *pAutonomusStream = autonomusStream;
  for (int i = 0; sizeof(autonomusStream) > i; i += 5) {
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

extern bool isLeftOpen;
extern bool isRightOpen;

std::ofstream ofs("/usd/autonomusStream.h");
void startWriteAutonomusStream() {
  printf("Autonomus begin to be write\n");
  ofs << "#include \"main.h\"\n"
      << "static const int autonomusStream[] = {\n";
}

void writeAutonomusStream() {
  ofs << leftFrontDiveTrainMotor.get_voltage() << ",\t"
      << rightFrontDiveTrainMotor.get_voltage() << ",\t"
      << launcherAMotor.get_voltage() << ",\t"
      << rightTriaballGraberMotor.get_voltage() << ",\t" << isLeftOpen << ",\t"
      << isRightOpen << ",\n";
}

void finishWritingAutonomusStream() {
  printf("Autonomus finish being written\n");
  ofs << "\n};";
  ofs.close();
}
