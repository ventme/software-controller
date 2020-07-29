#include "Encoder.h"
#include "Motor.h"

void ServoInit();
void ServoClearCount();
int ServoGetVelocity();
void ServoSetTargetPosition(int setpoint);
void ServoTask();
double ServoGetTargetPosition();
double ServoGetOutput();
