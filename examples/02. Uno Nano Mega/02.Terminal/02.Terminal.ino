/*
   Terminal Module is like a chat box. It allows you to send and receive commands between your
   board and smartphone.
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

   Explore more on: https://thestempedia.com/docs/dabble/terminal-module/
*/

#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <Dabble.h>
String Serialdata = "";
bool dataflag = 0;
void setup() {
  Serial.begin(9600);       // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);  //Change this baudrate as per your bluetooth baudrate. Connect bluetooth on digital pin 2(RX) and 3(TX) for Uno/Nano and on Serial3 pins for Mega.
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.      //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  while (Serial.available() != 0)
  {
    Serialdata = String(Serialdata + char(Serial.read()));
    dataflag = 1;
  }
  if (dataflag == 1)
  {
    Terminal.print(Serialdata);
    Serialdata = "";
    dataflag = 0;
  }
  if(Terminal.available())
  {
    while (Terminal.available() != 0)
    {
      Serial.write(Terminal.read());
    }
    Serial.println();
  }
}
