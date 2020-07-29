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

void MotorStop() {
    digitalWrite(HBRIDGE_A_PIN, LOW);
    digitalWrite(HBRIDGE_B_PIN, LOW);
    analogWrite(HBRIDGE_PWM_PIN, 0);
  
}

void MotorHome(){
    if (homeSwitchPressed()){
        Serial.println("on home switch");
        // away from the home switch
        while (homeSwitchPressed()){
            MotorForward(HOMING_PWM);
            delay(100);
          Serial.println("homing 1 ");
        }
        // stop
//        MotorBackward(0);
        MotorStop();
    }
    Serial.println("off home switch");

    // go forward until home switch is pressed
    while (!homeSwitchPressed()){
        MotorBackward(HOMING_PWM);
        delay(100);
        Serial.println("homing 2 ");
    }
        delay(200);

    // go  until home switch is depressed
    while (homeSwitchPressed()){
        MotorForward(HOMING_PWM);
        Serial.println("homing 3 ");
        delay(100);
    }


    // stop
        MotorStop();
//    MotorForward(0);
    Serial.println("home");
}
