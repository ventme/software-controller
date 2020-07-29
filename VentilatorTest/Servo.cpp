#include "Servo.h"

#include <PID_v1.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
const float kP = 10;
const float kI = 0;
const float kD = 12;

PID myPID(&Input, &Output, &Setpoint, kP, kI, kD, DIRECT);

int lastMotorEncoderCount = 0;
int timer1_counter = 65411; // 65536 - 16MHz/128/1000Hz (64511 for 0.001) 
volatile int currentVelocity = 0;

volatile bool timeISRBusy = 0;
volatile bool timeISRFired = 0;

void ServoInit(){
    noInterrupts();           // disable all interrupts
    TCCR1A = 0;
    TCCR1B = 0;

    TCNT1 = timer1_counter;   // preload timer
    TCCR1B |= (1 << CS11);    // 128 prescaler 
    TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
    interrupts();             // enable all interrupts

    MotorInit();
    EncoderInit();   

    myPID.SetMode(AUTOMATIC);
    myPID.SetOutputLimits(-100,100);
    myPID.SetSampleTime(1); // 10 msec
}

void ServoClearCount(){
    noInterrupts();           // disable all interrupts
    EncoderClearCount();
    lastMotorEncoderCount = 0;
    currentVelocity = 0;
    interrupts();             // enable all interrupts
}

int ServoGetVelocity() {
    while (timeISRBusy);  // wait for timer ISR if busy
    return currentVelocity; 
}

void ServoSetTargetPosition(int setpoint){
    Setpoint = setpoint;
}

double ServoGetTargetPosition(){
    return Setpoint;
}

double ServoGetOutput(){
    return Output;
}

uint32_t velocity_calc_timer = 0;
#define VCT_THRESH 100
void ServoTask(){
    if (timeISRFired) {
        timeISRFired = 0;
        Input = EncoderGetCount();
        myPID.Compute();

        if (Output >= 0)
            MotorForward(abs(Output));
        else
            MotorBackward(abs(Output));


      if (millis() - velocity_calc_timer > VCT_THRESH) {  
        int cnt = EncoderGetCount();
        currentVelocity = (cnt - lastMotorEncoderCount); // not scaled
        lastMotorEncoderCount = cnt;
        velocity_calc_timer = millis();
      }
    }
}

ISR(TIMER1_OVF_vect)        // interrupt service routine - tick every 0.001 sec
{
  timeISRBusy = 1;

  TCNT1 = timer1_counter;   // set timer

  timeISRBusy = 0;
  
  timeISRFired = 1; // tell ServoTask its time to calculate
}
