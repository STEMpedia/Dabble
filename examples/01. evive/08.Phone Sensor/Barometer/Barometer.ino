/*
   If your smartphone has Barometer sensor support then this code helps in accessing that sensor's value through Dabble app.

   You can reduce the size of library compiled by enabling only those modules that you want to
   use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/phone-sensors-module/
*/
#define CUSTOM_SETTINGS
#define INCLUDE_SENSOR_MODULE
#include <evive.h>
#include <Dabble.h>


void setup() {
  Serial.begin(250000);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(115200);      //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  print_Barometer_data();
}

void print_Barometer_data()
{
  Serial.print("Barometer: ");
  Serial.println(Sensor.getdata_Barometer(), 7);
  Serial.println();
}


