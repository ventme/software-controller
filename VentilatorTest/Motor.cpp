#include "Arduino.h"
#include "Constants.h"
#include "Motor.h"

void MotorInit(){
    pinMode(HBRIDGE_PWM_PIN, OUTPUT);
    analogWrite(HBRIDGE_PWM_PIN, 0);

    pinMode(HBRIDGE_A_PIN, OUTPUT);
    pinMode(HBRIDGE_B_PIN, OUTPUT);
    digitalWrite(HBRIDGE_A_PIN, LOW);
    digitalWrite(HBRIDGE_B_PIN, LOW);
}

void MotorForward(uint8_t rate){
    digitalWrite(HBRIDGE_A_PIN, HIGH);
    digitalWrite(HBRIDGE_B_PIN, LOW);
    analogWrite(HBRIDGE_PWM_PIN, rate);
}

void MotorBackward(uint8_t rate){
    digitalWrite(HBRIDGE_A_PIN, LOW);
    digitalWrite(HBRIDGE_B_PIN, HIGH);
    analogWrite(HBRIDGE_PWM_PIN, rate);
}

void MotorHome(){
    if (homeSwitchPressed()){

        // away from the home switch
        while (homeSwitchPressed()){
            MotorBackward(HOMING_PWM);
            delay(1);
        }
    }
    // stop
    MotorBackward(0);

    // go forward until home switch is released
    while (!homeSwitchPressed()){
        MotorForward(HOMING_PWM);
        delay(1);
    }

    // stop
    MotorForward(0);
}
