/* Pin State Monitor is made for monitoring status of analog and digital pins of your board.


   You can reduce the size of library compiled by enabling only those modules that you want to
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
  Serial.begin(9600);       // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);   //Change this baudrate as per your bluetooth baudrate. Connect bluetooth on digital pin 2(RX) and 3(TX) for Uno/Nano and on Serial3 pins for Mega.
}

void loop() {
  Dabble.processInput();      //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  PinMonitor.sendDigitalData();
  PinMonitor.sendAnalogData();
}
