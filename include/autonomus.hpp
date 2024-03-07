#include "main.h"

class Autonomus {
public:
  Autonomus();
  void readAutonomusStream();
  void writeAutonomusStream();

private:
  int counter;
};
