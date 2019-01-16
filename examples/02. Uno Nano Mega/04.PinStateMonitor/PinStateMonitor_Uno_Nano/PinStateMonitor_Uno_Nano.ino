/*
   Pin State Monitor is made for monitoring status of analog and digital pins of your board.
   In this example bluetooth is to be connected on HardwareSerial0 for Uno and Nano Boards.

   Pin Connection:
   Bluetooth        UNO/NANO
   TX               0 (RX)
   RX               1 (TX)


   WARNING:
   Since HardwareSerial0 is also used for code uploading process as well, unplug bluetooth from your board while uploading code.
   You can upload code first and then connect bluetooth to your board after code has been uploaded successfully.

   You can reduce the size of library compiled by enabling only those modules that you want
   use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.
  
   Explore more on: https://thestempedia.com/docs/dabble/pin-state-monitor-module/
*/


#define CUSTOM_SETTINGS
#define INCLUDE_PINMONITOR_MODULE
#include <Dabble.h>


void setup() {
  /*
     NOTE: PinMonitor only displays status of the pins of your board. It does not configure pinMode of the pins.
     So if there is any necessity to define pinMode then declare it setup as per requirement.
  */
  Serial.begin(9600);      //Connect bluetooth to HardwareSerial0 pins 0 and 1 of you UNO/NANO board.
  Dabble.begin(Serial);    //PLEASE REMOVE BLUETOOTH WHILE UPLOADING CODE ON YOUR BOARD.
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.    //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  PinMonitor.sendDigitalData();
  PinMonitor.sendAnalogData();
}
