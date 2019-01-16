/*
   Pin State Monitor is made for monitoring status of analog and digital pins of your board.
   In this example bluetooth is to be connected on HardwareSerial0 for Uno and Nano Boards.

   You can reduce the size of library compiled by enabling only those modules that you want
   to use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/pin-state-monitor-module/
*/

#define CUSTOM_SETTINGS
#define INCLUDE_PINMONITOR_MODULE
#include <evive.h>
#include <Dabble.h>


void setup() {
  /*
     NOTE: PinMonitor only displays status of the pins of your board. It does not configure pinMode of the pins.
     So if there is any necessity to define pinMode then declare it setup as per requirement.
  */
  Serial.begin(250000);    // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(115200);    //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  PinMonitor.sendDigitalData();
  PinMonitor.sendAnalogData();
  delayMicroseconds(20);
}
