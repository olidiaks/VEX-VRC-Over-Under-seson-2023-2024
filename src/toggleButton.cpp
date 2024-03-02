#include "main.h"

ToggleButton::ToggleButton(pros::controller_digital_e_t button)
    : button{button} {};

const bool ToggleButton::getState() { return isPressed; }

const void ToggleButton::updateStatus() {
  if (controller.get_digital(button)) {
    if (!wasPressedLastTimeWhenWasCheck) {
      isPressed = true;
      wasPressedLastTimeWhenWasCheck = true;
    }

    if (wasPressedLastTimeWhenWasCheck) {
      isPressed = true;
    }
  } else
    wasPressedLastTimeWhenWasCheck = false;
}

void updateStatusOfAllToogleButtons(){

}
