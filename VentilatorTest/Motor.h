#include "Constants.h"

inline bool homeSwitchPressed() { return digitalRead(HOME_PIN) == HIGH; }

void MotorInit();
void MotorForward(uint8_t rate);
void MotorBackward(uint8_t rate);
void MotorHome();
