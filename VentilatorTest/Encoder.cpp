#include "Arduino.h"
#include "Constants.h"

volatile int MotorEncoderCount = 0; // so a the motor has two encoders.. they are a square pulse that is 90 degrees out of phase.. you can tell direction by the channel that pulses first

void MotorEncoderAISR();
void MotorEncoderBISR();

void EncoderInit(){
    pinMode(ENCODER_A_PIN, INPUT);
    pinMode(ENCODER_B_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCODER_A_PIN), MotorEncoderAISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_B_PIN), MotorEncoderBISR, CHANGE);

    MotorEncoderCount = 0;
}

void MotorEncoderAISR(){
  if (digitalRead(ENCODER_A_PIN) && !digitalRead(ENCODER_B_PIN)) {
    MotorEncoderCount++;
  }
  
  if (digitalRead(ENCODER_A_PIN) && digitalRead(ENCODER_B_PIN)) {
    MotorEncoderCount--;
  } 

  if (!digitalRead(ENCODER_A_PIN) && !digitalRead(ENCODER_B_PIN)) {
    MotorEncoderCount--;
  }
  
  if (!digitalRead(ENCODER_A_PIN) && digitalRead(ENCODER_B_PIN)) {
    MotorEncoderCount++;
  } 
}

void MotorEncoderBISR(){
  if (digitalRead(ENCODER_B_PIN) && !digitalRead(ENCODER_A_PIN)) {
    MotorEncoderCount--;
  }
  
  if (digitalRead(ENCODER_B_PIN) && digitalRead(ENCODER_A_PIN)) {
    MotorEncoderCount++;
  } 

  if (!digitalRead(ENCODER_B_PIN) && !digitalRead(ENCODER_A_PIN)) {
    MotorEncoderCount++;
  }
  
  if (!digitalRead(ENCODER_B_PIN) && digitalRead(ENCODER_A_PIN)) {
    MotorEncoderCount--;
  }
}

int EncoderGetCount() {
    return MotorEncoderCount;
}

void EncoderClearCount() {
    MotorEncoderCount = 0;
}
