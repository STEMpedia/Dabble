/*
   Led Brightness Control Module allows user to control any digital pin on their board. They can turn pin ON or OFF, can 
   also vary its PWM if that functionality is supported on that pin.
   NOTE:
   1)For Arduino Mega Connect Bluetooth on Serial3 pins.
   2)For Arduino Uno/Nano library uses SoftwareSerial,hence pin 2 and pin 3 are used
   as RX and TX pins respectively on SoftwareSerial.Hence with arduino Uno
   follow below connections for bluetooth.
   UNO  - BLUETOOTH
   2    - TX
   3    - RX

   3)For Uno/Nano keep bluetooth Baudrate below 38400.
   Explore more on: https://thestempedia.com/docs/dabble/led-brightness-control-module/ 
*/

#define CUSTOM_SETTINGS
#define INCLUDE_LEDCONTROL_MODULE
#include <Dabble.h>

void setup() {
  Serial.begin(250000);
  Dabble.begin(9600);    //Change this baudrate as per your bluetooth baudrate. Connect bluetooth on digital pin 2(RX) and 3(TX) for Uno/Nano and on Serial3 pins for Mega.

}

void loop() {
  Dabble.processInput();          //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile. 
  Serial.print("Led:");
  Serial.print(LedControl.getpinNumber());
  Serial.print('\t');
  Serial.print("State:");          //0 suggests Led
  Serial.print(LedControl.getpinState());
  Serial.print('\t');
  Serial.print("Brightness:");
  Serial.println(LedControl.readBrightness());

  // put your main code here, to run repeatedly:

}
