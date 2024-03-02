#include "main.h"
#include "pros/adi.h"
#include "pros/misc.h"

bool isLeftOpen = false;
bool isRightOpen = false;

void leftAirSystemHandler(const bool isToogle, const bool isOpen) {
  isLeftOpen = isToogle ? !isLeftOpen : isOpen;
  pros::c::adi_digital_write(2, isLeftOpen);
}

void rightAirSystemHandler(const bool isToogle, const bool isOpen) {
  isRightOpen = isToogle ? !isRightOpen : isOpen;
  pros::c::adi_digital_write(3, isRightOpen);
}

void airSystemHandler(const bool isToogle, const bool isOpen) {
  leftAirSystemHandler(isToogle, isOpen);
  rightAirSystemHandler(isToogle, isOpen);
}

ToggleButton leftToggleButtonForAirStyem(pros::E_CONTROLLER_DIGITAL_L2);
ToggleButton rightToggleButtonForAirSystem(pros::E_CONTROLLER_DIGITAL_R2);

void airSystemSetAirSystemBasedOnControllerAction() {
  leftToggleButtonForAirStyem.updateStatus();
  rightToggleButtonForAirSystem.updateStatus();

  if (leftToggleButtonForAirStyem.getState()) leftAirSystemHandler(true);
  if (rightToggleButtonForAirSystem.getState()) rightAirSystemHandler(true);
}
