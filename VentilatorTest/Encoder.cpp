#include "Arduino.h"
#include "Constants.h"

volatile int MotorEncoderCount = 0; // so a the motor has two encoders.. they are a square pulse that is 90 degrees out of phase.. you can tell direction by the channel that pulses first

void MotorEncoderISR();

void EncoderInit(){
    pinMode(ENCODER_A_PIN, INPUT);
    pinMode(ENCODER_B_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCODER_A_PIN), MotorEncoderISR, RISING);

    MotorEncoderCount = 0;
}

void MotorEncoderISR(){
  // add 1 to count for CW
  if (digitalRead(ENCODER_A_PIN) && !digitalRead(ENCODER_B_PIN)) {
    MotorEncoderCount++;
  }
  // subtract 1 from count for CCW
  if (digitalRead(ENCODER_A_PIN) && digitalRead(ENCODER_B_PIN)) {
    MotorEncoderCount--;
  } 
}

int EncoderGetCount() {
    return MotorEncoderCount;
}

void EncoderClearCount() {
    MotorEncoderCount = 0;
}