/*
   MotorControl Module is used to control actuators like DC motors and Servos.
   This code is used for controlling two servos and two DC motors with evive.

   NOTE: In this code motors are connected on motor channel M1 and M2, since
   servo channels S1 and S2 share same pins as motor channels hence servos are connected on other
   digital pins instead of servo channels.

   You can reduce the size of library compiled by enabling only those modules that you want to
   use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/motor-control-module/

*/
#define CUSTOM_SETTINGS
#define INCLUDE_MOTORCONTROL_MODULE
#include <evive.h>
#include <Dabble.h>
motorControls Control;
Servo servo1;
Servo servo2;

uint8_t servo1_pin = 4;
uint8_t servo2_pin = 5;

void setup() {
  Serial.begin(250000);         // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(115200);         //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.              //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  servo1.write(Control.getangle_Servo1());
  servo2.write(Control.getangle_Servo2());
  Control.runMotor1();             //This is for motor channel M1 on evive.
  Control.runMotor2();             //This is for motor channel M2 on evive.
}
