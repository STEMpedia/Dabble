#include <evive.h>
#include "OscilloscopeModule.h"
void setup() {
  /*
   NOTE:
   Oscilloscope module does not follow standard procedure of data transfer link other modules.
   Before connecting with bluetooth open Oscilloscope module first. 
   */
   Serial3.begin(115200);         //set this baurate as per your bluetooth baudrate
   Oscilloscope.begin(Serial3);   //this function wait for connection with Dabble App
}

void loop() {
 Oscilloscope.sendDataChannel1(analogRead(POT1));  //plotting potentiometer data on oscilloscope module in Dabble.
 //Oscilloscope.sendDataChannel2(analogRead(POT2));  //Uncomment this if you want to send Data on Channel 2 as well.
}