/*
  If there is temperature sensor in your smartphone then you can access it through this example.
  Explore more on: https://thestempedia.com/docs/dabble/phone-sensors-module/
 */
#define CUSTOM_SETTINGS
#define INCLUDE_SENSOR_MODULE
#include <evive.h>
#include <Dabble.h>


void setup() {
  Serial.begin(250000);
  Dabble.begin(115200);     //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  print_Temperature_data();
}

void print_Temperature_data()
{
  Serial.print("TEMPERATURE: ");
  Serial.println(Sensor.getdata_Temperature(), 7);
  Serial.println();
}

