/*
 * This code shows how to set pins of your own choice for 
 * serial communication of UNO with HC-05.
 * In all the examples of Dabble library pin 2 and pin 3 of 
 * UNO are used by default for Serial communication with HC-05.
 * 
 * For this Led control module is used. Through this example 
 * you can control any desired pin on your device.
 */
#define CUSTOM_SETTINGS
#define INCLUDE_LEDCONTROL_MODULE
#include <Dabble.h>
void setup() {
  Serial.begin(9600);       // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600,4,5);  //(baudrate, RX pin, TX pin)
  // put your setup code here, to run once:
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
    

}
