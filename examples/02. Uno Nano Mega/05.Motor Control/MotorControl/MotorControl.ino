/*
  MotorControl Module is used to control actuators like DC motors and Servos.
  NOTE:
  1)For Arduino Mega Connect Bluetooth on Serial3 pins.
  2)For Arduino Uno/Nano library uses SoftwareSerial,hence pin 2 and pin 3 are used
  as RX and TX pins respectively on SoftwareSerial.Hence with arduino Uno
  follow below connections for bluetooth.
  UNO  - BLUETOOTH
  2    - TX
  3    - RX

  3)For Uno/Nano keep bluetooth Baudrate below 38400.

   You can reduce the size of library compiled by enabling only those modules that you want
   to use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more: https://thestempedia.com/docs/dabble/motor-control-module/
*/

#define CUSTOM_SETTINGS
#define INCLUDE_MOTORCONTROL_MODULE
#include <Servo.h>
#include <Dabble.h>

uint8_t PWM_m1 = 6;    //Must be a PWM pin (PWM pins have ~ marked beside their number markings.)
uint8_t Dir1_m1 = 4;
uint8_t Dir2_m1 = 7;
uint8_t PWM_m2 = 5;    //Must be a PWM pin
uint8_t Dir1_m2 = 8;
uint8_t Dir2_m2 = 12;

Servo servo1;
Servo servo2;
motorControls Control = motorControls(PWM_m1, Dir1_m1, Dir2_m1, PWM_m2, Dir1_m2, Dir2_m2);

uint8_t servo1_pin = 10;
uint8_t servo2_pin = 11;

void setup() {
  Serial.begin(9600);       // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);     //Change this baudrate as per your bluetooth baudrate. Connect bluetooth on digital pin 2(RX) and 3(TX) for Uno/Nano and on Serial3 pins for Mega.
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  servo1.write(Control.getangle_Servo1());
  servo2.write(Control.getangle_Servo2());
  Control.runMotor1();
  Control.runMotor2();
}
