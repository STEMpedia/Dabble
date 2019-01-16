/*
 * For arduino Mega Board default pins used with bluetooth
 * are Serial3 pins. You can use Serial pins of your choice.
 * This example demonstartes how it can be done.
 * 
 * For this Led control module is used. Through this example 
 * you can control any desired pin on your device.
 */
#define CUSTOM_SETTINGS
#define INCLUDE_LEDCONTROL_MODULE
#include <Dabble.h>
void setup() {
  Serial.begin(9600);     // make sure your Serial Monitor is also set at this baud rate.
  Serial2.begin(115200);  //enter your bluetooth baudrate here.
  Dabble.begin(Serial2);
}

void loop() {
  Dabble.processInput();
}
