# Vent Me Arduino Software Controller

We need to make software to do this: 
https://e-vent.mit.edu/controls/high-level-controls/
** You might need to register with MIT to get access to that. 

The vent.me software is ardunio embedded software.

Ardunio system board
* ATmega2560 Processor
* Honeywell TruStability® Board Mount Pressure (1 PSI Differential)
* ST VNH5019A H-Bridge Motor Driver (<30 amp peak)
* Breakouts for rotary encoder and/orÂ Angular Measurement
* Breakouts for 2 limit switches

Display Board
* 4x20 LED Display
* 4 x Rotary knobs
* 1 x Confirm button
* 1 x Alarm SilenceÂ button
* 1 x Mode switchÂ 
* 1 x E-Stop Switch
* 1 x Power Switch

The libraries for the Honeywell Sensor are located here: 
https://playground.arduino.cc/Main/HoneywellTruStabilitySSC-HSCPressureSensors/

We are using this library for the motor controller: 
https://github.com/pololu/dual-vnh5019-motor-shield

