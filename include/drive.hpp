#include "main.h"

extern int speedPrecent;

void setDriveTrain(const int leftMotors, const int rightMotors);

void setMotorsToDriveFromControler(const int speedPrecent);

void changeSpeedOfDriveTraind(int *pSpeedPrecent);

void resetDriveTrainEncoders();

double avgDistanceFromDriveTrainEncoders();

void moveRobot(const int distance, const int voltage = 12000);

void turnRobot(const int degress, const int voltage = 120000);
