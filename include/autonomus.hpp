#include "pros/motors.hpp"

class Autonomus {
public:
  Autonomus();
  void readAutonomusStream();
  void writeAutonomusStream();

private:
  bool moveMotor(const pros::Motor motorFront, const pros::Motor motorBack, const int i, const int motorId);
};
