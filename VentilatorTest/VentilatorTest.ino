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
}

int motorTimerStart = 0;
#define motorTimerThresh  100

void loop() {
  Serial.print(digitalRead(8));
  Serial.print(",");
  Serial.print(digitalRead(9));
  Serial.print(",");
  Serial.print(EncoderGetVelocity());
  Serial.print(",");
  Serial.println(EncoderGetCount());

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
   if ((MotorDirection == 1 && digitalRead(8)) 
    || (MotorDirection == 0 && digitalRead(9)))
      MotorDirection = !MotorDirection;
  }
  
  delay(10);   // in microprocessor land this is very bad practice... we should always read the amount of time the chip has been running and us it for timing.. when this function happens the chip does NOTHING .. we have only one core.. .. no forking.. think about the oldschool assemblh days... 
 

}


