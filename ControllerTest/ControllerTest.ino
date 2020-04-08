#include <Wire.h>  // This handles the interface for anything on the i2c bus ( display, pressure sensor..etc. ) 
#include <LiquidCrystal_I2C.h> //used to interface with the display
#include <SSC.h> // used to interface with the pressure sensor

bool MotorDirection = 0;  // store motor direction here 

SSC ssc(0x28);  // honeywell sensor has a address of 28

volatile int MotorEncoderACount = 0; // so a the motor has two encoders.. they are a square pulse that is 90 degrees out of phase.. you can tell direction by the channel that pulses first
volatile int MotorEncoderBCount = 0;
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

void setup() {
  // put your setup code here, to run once:
pinMode(39, OUTPUT);  // define the buzzer pin as an output.. .. really shit should be all defined at the top of the code using something like "BuzzerPin = 39" .. but hell this is a test program..

// here we define the interupts and the routines they will run when they happen. .. its a square wave so we only really want to count the pulses once.. I chose the rising edge. 
pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), MotorEncoderA, RISING);

pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(3), MotorEncoderB, RISING);


lcd.init();                      // initialize the lcd 
  lcd.backlight();


// endstops .. when the claw has hit its limits. 
  pinMode(8, INPUT);
  pinMode(9, INPUT);

Serial.begin(9600);  // for debugging 


analogWrite(7, 0);  // this is the pin that controls the speed of the motor.. we make sure its shut down right away.. when electronics startup they are in an unknown state. 


// defiintions for the Pressure Sensor
ssc.setMinRaw(0);
  ssc.setMaxRaw(16383);
  ssc.setMinPressure(0.0);
  ssc.setMaxPressure(1);
  //ssc.start();
   Serial.println(ssc.start());
}

void loop() {
// make words happen 
lcd.setCursor(3,0);
  lcd.print("Words Go Here");

 // The following 3 lines turnt he buzzer on and off for 100ms.. i commented them out because it was making my dog crazy

//digitalWrite(39, HIGH);
//delay(100);
//digitalWrite(39, LOW);


if ( MotorDirection == 0 )  // motor goes one way
{
  digitalWrite(38, HIGH);
digitalWrite(37, LOW);
analogWrite(7, 255);
}

if ( MotorDirection == 1 )  // or the other 
{
  digitalWrite(38, LOW);
digitalWrite(37, HIGH);
analogWrite(7, 255);
}

// serial debugging information

  Serial.print("Volume Setpoint: ");
  Serial.println(analogRead(A0));

  Serial.print("BPM Setpoint: ");
  Serial.println(analogRead(A1));

  Serial.print("IE Ratio Setpoint: ");
  Serial.println(analogRead(A2));

  Serial.print("Pressure Setpoint: ");
  Serial.println(analogRead(A3));

  Serial.print("Mode Select: ");
  Serial.println(digitalRead(4));
  Serial.println();

 Serial.print("Confirm Button: "); // these buttons are tied to a "De bouncing" circuit so their logic is inverted.. 0 means pushed.. 1 means its left alone
  Serial.println(digitalRead(5));
  Serial.println();

 Serial.print("Silence Button: ");
  Serial.println(digitalRead(6));
  Serial.println();

Serial.print("Motor A Count: ");  // print the interupt counts.. these should actually be defined uptop as "unsigned intergers" .. or longs or whatever memmory allows for... just a heads up.. they will roll over and fuck you! 
  Serial.println(MotorEncoderACount);
  Serial.println();
Serial.print("Motor B Count: ");
  Serial.println(MotorEncoderBCount);
  Serial.println();

ssc.update();
Serial.print("Pressure Reading: ");
 Serial.println(ssc.pressure());


 Serial.print("Endstop A: ");
  Serial.println(digitalRead(8));
  Serial.println();

 
 Serial.print("Endstop B: ");
  Serial.println(digitalRead(9));
  Serial.println();


Serial.println(MotorDirection);
MotorDirection = !MotorDirection;
  delay(1000);   // in microprocessor land this is very bad practice... we should always read the amount of time the chip has been running and us it for timing.. when this function happens the chip does NOTHING .. we have only one core.. .. no forking.. think about the oldschool assemblh days... 
 

}


// interrupt sub routines
void MotorEncoderA(){
  MotorEncoderACount ++;
}

void MotorEncoderB(){
  MotorEncoderBCount ++;
}
