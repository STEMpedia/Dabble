/*
	Explore more: https://thestempedia.com/docs/dabble/oscilloscope-module/
*/
#include "OscilloscopeModule.h"
void setup() {
  /*
    NOTE:
    Oscilloscope module does not follow standard procedure of data transfer like other modules.
    Before connecting with bluetooth open Oscilloscope module first.
  */
  Serial.begin(115200);         //For increasing data transfer speed over bluetooth connect it on HardwareSerial 0 for Uno or Nano and on either of HardwareSerial 1,2,3 for Arduino Mega.
  Oscilloscope.begin(Serial);   //this function wait for connection with Dabble App
}

void loop() {
  Oscilloscope.sendDataChannel1(analogRead(A0));  //you can connect a potentiometer or any analog sensor to visualize its Data  on Oscilloscope Module
  //Oscilloscope.sendDataChannel2(analogRead(A1));  //Uncomment this if you want to send Data on Channel 2 as well.
}