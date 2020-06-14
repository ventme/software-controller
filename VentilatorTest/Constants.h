/**
 * MIT Emergency Ventilator Controller
 * 
 * MIT License:
 * 
 * Copyright (c) 2020 MIT
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * Constants.h
 * Defines all the global constants used in `e-vent.ino`.
 */

#ifndef Constants_h
#define Constants_h

#define USE_VENTME_HW

// States
enum States {
  DEBUG_STATE,       // 0
  IN_STATE,          // 1
  HOLD_IN_STATE,     // 2
  EX_STATE,          // 3
  PEEP_PAUSE_STATE,  // 4
  HOLD_EX_STATE,     // 5
  PREHOME_STATE,     // 6
  HOMING_STATE,      // 7
  OFF_STATE          // 8
};

// Serial baud rate
const long SERIAL_BAUD_RATE = 115200;

// Flags
const bool DEBUG = false; // For controlling and displaying via serial
const bool ASSIST_CONTROL = false; // Enable assist control

// Timing Settings
const float LOOP_PERIOD = 0.03;       // The period (s) of the control loop
const float HOLD_IN_DURATION = 0.1;  // Duration (s) to pause after inhalation
const float MIN_PEEP_PAUSE = 0.05;    // Time (s) to pause after exhalation / before watching for an assisted inhalation
const float MAX_EX_DURATION = 1.00;   // Maximum exhale duration (s)

// Homing Settings
const float HOMING_VOLTS = 30;  // The speed (0-255) in volts to use during homing
const float HOMING_PAUSE = 1.0; // The pause time (s) during homing to ensure stability
const int BAG_CLEAR_POS = 50;   // The goal position (clicks) to retract to clear the bag
const int BAG_CLEAR_TOL = 10;   // The tolerance (clicks) to consider clear of bag
const uint8_t HOMING_PWM = 30;
// Pins
#ifdef USE_VENTME_HW
// Port	    Arduino Pin	Connection
// PF0(ADC0)	A0	Volume Pot
// PF1(ADC1)	A1	BPM Pot
// PF2(ADC2)	A2	IE Ratio Pot
// PF3(ADC3)	A3	Pressure Pot          TODO XXX - AC PIN? 
// PF4(ADC4)	A4	Pressure Analog       This is using the i2c digital interface
// PF5(ADC5)	A5	Misc Analog           TODO XXX - not in reference design
// PF6(ADC6)	A6	Mode Select           TODO XXX - not in reference design
// PE3	      5	  Confirm 
// PH3	      6	  Silence               aka snooze
// PC1	      36	Emergency             TODO
// PC2	      35	Misc Button 0         Now the home switch
// PC3	      34	Misc Button 1         TODO
// PH5	      8	  Endstop A
// PH6	      9	  Endstop B
// PC6	      31	Led 0
// PC7	      30	Led 1                 TODO
// PJ0	      14	Led 2                 TODO
// PJ1	      15	External Alarm        TODO
// PD7	      38	Hbridge A
// PC0	      37	HBridge B
// PH4	      7	  Hbridge PWM
// PE4	      2	  Motor Encoder A
// PE5	      3	  Motor Encoder B
// PD2	      19	Hall Sensor A           TODO
// PD3	      18	Hall Sensor B           TODO

const int VOL_PIN = A0;
const int BPM_PIN = A1;
const int IE_PIN = A2;
const int AC_PIN = A3;              // TODO XXX not above? Same as Pressure Pot? 
const int HOME_PIN = 35;            // TODO XXX not above? 
const int BEEPER_PIN = 39;          // PG2 aka Digital pin 39 @ https://www.arduino.cc/en/Hacking/PinMapping2560
const int SNOOZE_PIN = 6;           // PH3 aka Digital pin 6
const int CONFIRM_PIN = 5;
const int SD_SELECT = 53;           // TODO XXX same as mode select above? 
const int OFF_PIN = 45;             // TODO XXX not above?
const int LED_ALARM_PIN = 31;       // TODO XXX Which LED for alarm? use LED0 for now

const int ENCODER_A_PIN = 2;
const int ENCODER_B_PIN = 3;
const int HBRIDGE_A_PIN = 38;
const int HBRIDGE_B_PIN = 37;
const int HBRIDGE_PWM_PIN = 7;
const int ENDSTOP_A_PIN = 8;
const int ENDSTOP_B_PIN = 9;
#else
const int VOL_PIN = A0;
const int BPM_PIN = A1;
const int IE_PIN = A2;
const int AC_PIN = A3;
const int PRESS_SENSE_PIN = A4;
const int HOME_PIN = 10;
const int BEEPER_PIN = 11;
const int SNOOZE_PIN = 43;
const int CONFIRM_PIN = 41;
const int SD_SELECT = 53;
const int OFF_PIN = 45;
const int LED_ALARM_PIN = 12;
const int LCD_RS_PIN = 9;
const int LCD_EN_PIN = 8;
const int LCD_D4_PIN = 7;
const int dLCD_D5_PIN = 6;
const int LCD_D6_PIN = 5;
const int LCD_D7_PIN = 4;
#endif

// Control knob mappings
const int BPM_MIN = 10;
const int BPM_MAX = 35;
const int BPM_RES = 1;
const float IE_MIN = 1;
const float IE_MAX = 4;
const float IE_RES = 0.1;
const int VOL_MIN = 100;
const int VOL_MAX = 800; 
const int VOL_RES = 25; 
const float AC_MIN = 2;
const float AC_MAX = 5;
const float AC_RES = 0.1;
const int ANALOG_PIN_MAX = 1023; // The maximum count on analog pins

// Bag Calibration for AMBU Adult bag
const struct {float a, b, c;} COEFFS{1.29083271e-03, 4.72985182e-01, -7.35403067e+01};

// Safety settings
const float MAX_PRESSURE = 40.0;        // Trigger high pressure alarm
const float MIN_PLATEAU_PRESSURE = 5.0; // Trigger low pressure alarm
const float MAX_RESIST_PRESSURE = 2.0;  // Trigger high-resistance notification
const float MIN_TIDAL_PRESSURE = 5.0;   // Trigger no-tidal-pressure alarm
const float VOLUME_ERROR_THRESH = 50.0; // Trigger incomplete breath alarm
const int MAX_MOTOR_CURRENT = 1000;     // Trigger mechanical failure alarm. Units (10mA)
const float TURNING_OFF_DURATION = 5.0; // Turning-off alarm is on for this duration (s)
const float MECHANICAL_TIMEOUT = 1.0;   // Time to wait for the mechanical cycle to finish before alarming

// PID values for auto-tuned for PG188
const unsigned long QPPS = 2000;
const float VKP = 6.38650;
const float VKI = 0.0;
const float VKD = 0.0;
const float PKP = 70.0;
const float PKI = 0.2;
const float PKD = 200.0;
const unsigned long KI_MAX = 10;
const unsigned long DEADZONE = 0;
const unsigned long MIN_POS = -100;
const unsigned long MAX_POS = 700;
const unsigned long VEL_MAX = 1800;     // Maximum velocity (clicks/s) to command
const unsigned long ACC_MAX = 200000;   // Maximum acceleration (clicks/s^2) to command

// Roboclaw
const unsigned int ROBOCLAW_ADDR = 0x80;
const long ROBOCLAW_BAUD = 38400;
const unsigned long ROBOCLAW_MAX_CURRENT = 2000;    //Safety shutoff in units of 10mA

#endif
