/*
 * For arduino Mega Board default pins used with bluetooth
 * are Serial3 pins. You can use Serial pins of your choice.
 * This example demonstartes how it can be done.
 */
#define CUSTOM_SETTINGS
#define INCLUDE_LEDCONTROL_MODULE
#include <Dabble.h>
void setup() {
  Serial.begin(250000);
  Serial2.begin(115200);  //enter your bluetooth baudrate here.
  Dabble.begin(Serial2);
}

void loop() {
  Dabble.processInput();
}
