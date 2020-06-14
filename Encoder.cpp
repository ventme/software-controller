#include "Arduino.h"
#include "Constants.h"

volatile int MotorEncoderCount = 0; // so a the motor has two encoders.. they are a square pulse that is 90 degrees out of phase.. you can tell direction by the channel that pulses first
int lastMotorEncoderCount = 0;
int timer1_counter = 59286;   // preload timer 65536-16MHz/256/2Hz (34286 for 0.5sec) (59286 for 0.1sec); //for timer
int currentVelocity = 0;
volatile bool timeISRBusy = 0;

void MotorEncoderISR();

void EncoderInit(){
    // here we define the interupts and the routines they will run when they happen. .. its a square wave so we only really want to count the pulses once.. I chose the rising edge. 
    pinMode(ENCODER_A_PIN, INPUT);
    pinMode(ENCODER_B_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCODER_A_PIN), MotorEncoderISR, RISING);

    MotorEncoderCount = 0;

    noInterrupts();           // disable all interrupts
    TCCR1A = 0;
    TCCR1B = 0;

    TCNT1 = timer1_counter;   // preload timer
    TCCR1B |= (1 << CS12);    // 256 prescaler 
    TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
    interrupts();             // enable all interrupts
}

// interrupt sub routines TODO - untested
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

void EncoderClearCount(){
    noInterrupts();           // disable all interrupts
    MotorEncoderCount = 0;
    lastMotorEncoderCount = 0;
    currentVelocity = 0;
    interrupts();             // enable all interrupts
}

const float&  EncoderGetVelocity() {
    while (timeISRBusy);  // wait for timer ISR if busy
    return currentVelocity; 
}

ISR(TIMER1_OVF_vect)        // interrupt service routine - tick every 0.1sec
{
  timeISRBusy = 1;
  TCNT1 = timer1_counter;   // set timer
  currentVelocity = (lastMotorEncoderCount - MotorEncoderCount ) / 0.1; // can move devide for efficiency
  lastMotorEncoderCount = MotorEncoderCount;
  timeISRBusy = 0;
}
