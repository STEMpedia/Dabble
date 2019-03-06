
/*
   Terminal Module is like a chat box. It allows you to send and receive commands between your
   board and smartphone.

   You can reduce the size of library compiled by enabling only those modules that you
   want to use. For this first define CUSTOM_SETTINGS followed by defining
   INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/terminal-module/
*/
#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <evive.h>
#include <Dabble.h>
String Serialdata = "";
bool dataflag = 0;
void setup() {
  Serial.begin(250000);       // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(115200);       //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
}

void loop() {

  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
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
