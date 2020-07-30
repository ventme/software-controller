#include "Servo.h"

// add homing
// ensure limits are consisten after homing
// add position based PID

bool MotorDirection = 0;
uint32_t motorTimerStart = 0;

void setup() {
  // endstops .. when the claw has hit its limits. 
  pinMode(8, INPUT);
  pinMode(9, INPUT);

  Serial.begin(115200);  
//  Serial.println("booting");

  ServoInit();

  MotorHome();// ServoTask not running yet, homing is safe
  delay(100);
  ServoSetTargetPosition(0);
  EncoderClearCount();
  delay(2000);

  motorTimerStart = millis();

}

#define motorTimerThresh  2000

uint32_t printTimerStart = 0;
#define printTimerThresh 10

void loop() {
  ServoTask();

  if (millis() - printTimerStart > printTimerThresh) {
     Serial.print(ServoGetOutput());
     Serial.print(",");
     Serial.print(ServoGetVelocity());
     Serial.print(",");
     Serial.print(ServoGetTargetPosition());
     Serial.print(",");
     Serial.println(EncoderGetCount());
    printTimerStart = millis();
  }

  if (millis() - motorTimerStart < 5000)
  {
    ServoSetTargetPosition(700);
  }
  else if (millis() - motorTimerStart < 7500)
  {
    ServoSetTargetPosition(100);
  }
  else if (millis() - motorTimerStart  < 10000)
  {
    ServoSetTargetPosition(500);
  }
  else if (millis() - motorTimerStart  < 12500)
  {
    motorTimerStart = millis();
  }

  // delay(1);  
}
