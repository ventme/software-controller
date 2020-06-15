#include "Servo.h"

// add homing
// ensure limits are consisten after homing
// add position based PID

bool MotorDirection = 0;

void setup() {
  // endstops .. when the claw has hit its limits. 
  pinMode(8, INPUT);
  pinMode(9, INPUT);

  Serial.begin(115200);  // for debugging 
  Serial.println("booting");

  ServoInit();

  MotorHome();// ServoTask not running yet, homing is safe
  ServoSetTargetPosition(0);
  EncoderClearCount();
  delay(2000);
}

int motorTimerStart = 0;
#define motorTimerThresh  2000

int printTimerStart = 0;
#define printTimerThresh 100

void loop() {
  ServoTask();

  if (millis() - printTimerStart > printTimerThresh) {
    Serial.print(ServoGetTargetPosition());
    Serial.print(",");
    Serial.print(EncoderGetCount());
    Serial.print(",");
    Serial.println(ServoGetOutput());
    printTimerStart = millis();
  }

  // if (millis() - motorTimerStart > motorTimerThresh) {
  //   motorTimerStart = millis();
  //   MotorDirection = !MotorDirection;
  //   if ( MotorDirection == 0 )  // motor goes one way
  //   {
  //     ServoSetTargetPosition(100);
  //   }

  //   if ( MotorDirection == 1 )  // or the other 
  //   {
  //     ServoSetTargetPosition(10);
  //   }

  // }


  if (millis() - motorTimerStart > 10*motorTimerThresh) {
    ServoSetTargetPosition(0);
    motorTimerStart = 0;
  }
  else if (millis() - motorTimerStart > 5*motorTimerThresh) {
    ServoSetTargetPosition(10);
  }
  else if (millis() - motorTimerStart > motorTimerThresh) {
    ServoSetTargetPosition(100);
  }

  // delay(1);  
}


