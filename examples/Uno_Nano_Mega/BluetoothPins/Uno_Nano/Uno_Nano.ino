/*
 * This code shows how to set pins of your own choice for 
 * serial communication of UNO with HC-05.
 * In all the examples of Dabble library pin 2 and pin 3 of 
 * UNO are used by default for Serial communication with HC-05.
 */
#define CUSTOM_SETTINGS
#define INCLUDE_LEDCONTROL_MODULE
#include <Dabble.h>
void setup() {
  Serial.begin(250000);
  Dabble.begin(9600,4,5);  //(baudrate, RX pin, TX pin)
  // put your setup code here, to run once:
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  // put your main code here, to run repeatedly:

}
