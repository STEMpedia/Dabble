/*
   In this example you will be sending data of analog pin to your thingspeak channel.
   Data is send to field 1 of your thingspeak channel.   
   
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

   Explore more on: https://thestempedia.com/docs/dabble/internet-module/
*/
#define CUSTOM_SETTINGS
#define INCLUDE_INTERNET_MODULE
#include <Dabble.h>
String WRITE_KEY = "IXPXC82OLNNH1EBW";   //enter your thingspeak write key 
uint8_t pushButton = 4;
void setup() {
  Dabble.begin(9600); //Change this baudrate as per your bluetooth baudrate. Connect bluetooth on digital pin 2(RX) and 3(TX) for Uno/Nano and on Serial3 pins for Mega.
  pinMode(pushButton,INPUT_PULLUP);  
}

void loop() {
  Dabble.processInput(); //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  if(digitalRead(pushButton) == LOW)
  {
    Internet.updateThingspeakField(WRITE_KEY, 1, analogRead(A0));
    Dabble.delay(500);   //Debounce delay
  }
}
