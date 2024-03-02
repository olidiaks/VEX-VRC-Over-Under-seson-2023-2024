#include "main.h"
#include "pros/misc.h"

class ToggleButton {
private:
  bool isPressed;
  bool wasPressedLastTimeWhenWasCheck = false;
  const pros::controller_digital_e_t button;

public:
  ToggleButton(const pros::controller_digital_e_t button);
  const bool getState();
  const void updateStatus();
};

void updateStatusOfAllToogleButtons();
