/*
  Magnetometer block helps in accessing your mobile's magnetometer.
  Explore more on: https://thestempedia.com/docs/dabble/phone-sensors-module/
 */
#define CUSTOM_SETTINGS
#define INCLUDE_SENSOR_MODULE
#include <evive.h>
#include <Dabble.h>


void setup() {
  Serial.begin(250000);
  Dabble.begin(115200);    //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  print_Magnetometer_data();
}

void print_Magnetometer_data()
{
  Serial.print("X-axis: ");
  Serial.print(Sensor.getdata_Magnetometer_xaxis(), 7);
  Serial.print('\t');
  Serial.print("Y-axis: ");
  Serial.print(Sensor.getdata_Magnetometer_yaxis(), 7);
  Serial.print('\t');
  Serial.print("Z-axis: ");
  Serial.println(Sensor.getdata_Magnetometer_zaxis(), 7);
  Serial.println();
}



