/*
  Pin State Monitor is made for monitoring status of analog and digital pins of your board.
  In this example bluetooth is to be connected on HardwareSerial0 for Uno and Nano Boards.
  Explore more on: https://thestempedia.com/docs/dabble/pin-state-monitor-module/ 
 */

#define CUSTOM_SETTINGS
#define INCLUDE_PINMONITOR_MODULE
#include <evive.h>
#include <Dabble.h>


void setup() {
  /*
   * NOTE: PinMonitor only displays status of the pins of your board. It does not configure pinMode of the pins.
   * So if there is any necessity to define pinMode then declare it setup as per requirement.
   */
  Serial.begin(250000);
  Dabble.begin(115200);    //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  PinMonitor.sendDigitalData();
  PinMonitor.sendAnalogData();
  delayMicroseconds(20);
}
