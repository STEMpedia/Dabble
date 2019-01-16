/*
   Led Brightness Control Module allows user to control any digital pin on their board. They can turn pin ON or OFF, can
   also vary its PWM if that functionality is supported on that pin.

   You can reduce the size of library compiled by enabling only those modules that you want to
   use.For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/led-brightness-control-module/
*/
#define CUSTOM_SETTINGS
#define INCLUDE_LEDCONTROL_MODULE
#include <evive.h>
#include <Dabble.h>

void setup() {
  Serial.begin(250000);     // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(115200);     //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.

}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  Serial.print("Led:");
  Serial.print(LedControl.getpinNumber());
  Serial.print('\t');
  Serial.print("State:");          //0 if led is Off. 1 if led is On.
  Serial.print(LedControl.getpinState());
  Serial.print('\t');
  Serial.print("Brightness:");
  Serial.println(LedControl.readBrightness());
}
