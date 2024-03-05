#include "main.h"
#include "pros/misc.h"

bool isLeftOpen = false;
bool isRightOpen = false;

void leftAirSystemHandler(const bool isToogle, const bool isOpen) {
  printf("left wing update\n");
  isLeftOpen = isToogle ? !isLeftOpen : isOpen;
  leftWing.set_value(isLeftOpen);
}

void rightAirSystemHandler(const bool isToogle, const bool isOpen) {
  printf("right wing update\n");
  isRightOpen = isToogle ? !isRightOpen : isOpen;
  rightWing.set_value(isRightOpen);
}

void airSystemHandler(const bool isToogle, const bool isOpen) {
  leftAirSystemHandler(isToogle, isOpen);
  rightAirSystemHandler(isToogle, isOpen);
}

ToggleButton leftToggleButtonForAirStyem(pros::E_CONTROLLER_DIGITAL_L2);
ToggleButton rightToggleButtonForAirSystem(pros::E_CONTROLLER_DIGITAL_R2);

void airSystemSetAirSystemBasedOnControllerAction() {
  printf("update of air system is called\n");
  leftToggleButtonForAirStyem.updateStatus();
  rightToggleButtonForAirSystem.updateStatus();

  if (leftToggleButtonForAirStyem.getState()) leftAirSystemHandler(true);
  if (rightToggleButtonForAirSystem.getState()) rightAirSystemHandler(true);
}
