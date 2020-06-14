#include "Motor.h"
#include "Encoder.h"

// add homing
// ensure limits are consisten after homing
// add position based PID

bool MotorDirection = 0;

void setup() {
  // endstops .. when the claw has hit its limits. 
  pinMode(8, INPUT);
  pinMode(9, INPUT);

  Serial.begin(115200);  // for debugging 

  EncoderInit();
  MotorInit();

  MotorHome();
  EncoderClearCount();
  delay(2000);
}

int motorTimerStart = 0;
#define motorTimerThresh  100

int printTimerStart = 0;
#define printTimerThresh 100

void loop() {
  if (millis() - printTimerStart > printTimerThresh) {
    Serial.print(digitalRead(8));
    Serial.print(",");
    Serial.print(digitalRead(9));
    Serial.print(",");
    Serial.print(EncoderGetVelocity());
    Serial.print(",");
    Serial.println(EncoderGetCount());
    printTimerStart = millis();
  }

  if (millis() - motorTimerStart > motorTimerThresh) {
    if ( MotorDirection == 0 )  // motor goes one way
    {
      MotorBackward(0);
      MotorForward(20);
    }

    if ( MotorDirection == 1 )  // or the other 
    {
      MotorForward(0);
      MotorBackward(20);
    }
    motorTimerStart = millis();
   if (MotorDirection == 1 && digitalRead(8)) {
      MotorDirection = !MotorDirection;
   }
   if (MotorDirection == 0 && digitalRead(9)){
      MotorDirection = !MotorDirection;
   }
  }
  
  delay(1);  
 

}


