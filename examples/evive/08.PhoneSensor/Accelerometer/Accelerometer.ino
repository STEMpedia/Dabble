/*
  Accelerometer block of Phone sensor module allows you to access your smartphone's accelerometer values.
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
  print_Accelerometer_data();
}

void print_Accelerometer_data()
{
  Serial.print("X_axis: "); 
  Serial.print(Sensor.getdata_Accelerometer_xaxis(),4);      
  Serial.print('\t');
  Serial.print("Y_axis: ");
  Serial.print(Sensor.getdata_Accelerometer_yaxis(),4);
  Serial.print('\t');
  Serial.print("Z_axis: ");
  Serial.println(Sensor.getdata_Accelerometer_zaxis(),4);
  Serial.println();
}

