#include "main.h"

void twoDigitalButtonsTwoMotorsHandler(const pros::controller_digital_e_t buttonPositive, const pros::controller_digital_e_t buttonNegative, const pros::Motor motorA, pros::Motor motorB, const int voltageMultiplayer){
	const int power = voltageMultiplayer *  (buttonPositive - buttonNegative);
	motorA.move_voltage(power);
	motorB.move_voltage(power);
}
