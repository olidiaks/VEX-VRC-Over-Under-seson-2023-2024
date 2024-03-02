#include "main.h"
#include "pros/adi.h"

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

void airSystemSetAirSystemBasedOnControllerAction() {}
