#include "Servo.h"

#include <PID_v1.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
const float kP = 4;
const float kI = 0.1;
const float kD = 2;
// PKP, PKI, PKD
// const float PKP = 70.0;
// const float PKI = 0.2;
// const float PKD = 200.0;

// PID myPID(&Input, &Output, &Setpoint, PKP, PKI, PKD, DIRECT);
PID myPID(&Input, &Output, &Setpoint, kP, kI, kD, DIRECT);

int lastMotorEncoderCount = 0;
int timer1_counter = 59286;   // preload timer 65536-16MHz/256/2Hz (34286 for 0.5sec) (59286 for 0.1sec); //for timer
volatile int currentVelocity = 0;

volatile bool timeISRBusy = 0;
volatile bool timeISRFired = 0;

void ServoInit(){
    noInterrupts();           // disable all interrupts
    TCCR1A = 0;
    TCCR1B = 0;

    TCNT1 = timer1_counter;   // preload timer
    TCCR1B |= (1 << CS12);    // 256 prescaler 
    TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
    interrupts();             // enable all interrupts

    MotorInit();
    EncoderInit();   

    myPID.SetMode(AUTOMATIC);
    myPID.SetOutputLimits(-30,30);
    // myPID.SetOutputLimits(0,255);
    myPID.SetSampleTime(100); // 100 msec
}

void ServoClearCount(){
    noInterrupts();           // disable all interrupts
    EncoderClearCount();
    lastMotorEncoderCount = 0;
    currentVelocity = 0;
    interrupts();             // enable all interrupts
}

float ServoGetVelocity() {
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

void ServoTask(){
    if (timeISRFired) {
        timeISRFired = 0;
        Input = EncoderGetCount();
        myPID.Compute();
 
        Serial.print("servo task ");
        Serial.println(Output);

        if (Output >= 0)
            MotorBackward(abs(Output));
            // MotorForward(Output);
        else
            // MotorBackward(abs(Output));
            MotorForward(abs(Output));
    }
}

ISR(TIMER1_OVF_vect)        // interrupt service routine - tick every 0.1 sec
{
  timeISRBusy = 1;
  TCNT1 = timer1_counter;   // set timer
  int cnt = EncoderGetCount();
  currentVelocity = (cnt - lastMotorEncoderCount);
  lastMotorEncoderCount = cnt;
  timeISRBusy = 0;
  timeISRFired = 1; // tell ServoTask its time to calculate
}
