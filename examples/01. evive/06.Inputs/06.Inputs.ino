/*
   DabbleInputs module of your smartphone consists of two potentiometers, two slideswitches and two push button.

   You can reduce the size of library compiled by enabling only those modules that you want to
   use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/input-module/
*/
#define CUSTOM_SETTINGS
#define INCLUDE_DABBLEINPUTS_MODULE
#include <evive.h>
#include <Dabble.h>
void setup() {
  Serial.begin(250000);   // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(115200);   //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.

  Serial.print("Pot1:");
  Serial.print(Inputs.getvalue_Pot1());
  Serial.print('\t');
  Serial.print("Pot2:");
  Serial.print(Inputs.getvalue_Pot2());
  Serial.print('\t');
  Serial.print("SS1:");
  Serial.print(Inputs.getStatus_SlideSwitch1());
  Serial.print('\t');
  Serial.print("SS2:");
  Serial.print(Inputs.getStatus_SlideSwitch2());
  Serial.print('\t');
  Serial.print("TS1:");
  Serial.print(Inputs.getStatus_TactileSwitch1());
  Serial.print('\t');
  Serial.print("TS2:");
  Serial.print(Inputs.getStatus_TactileSwitch2());
  Serial.println();
}
