/*
   In this example you will be sending data of evive potentiometer to your thingspeak channel.
   Data is send to field 1 of your thingspeak channel.   
  
   You can reduce the size of library compiled by enabling only those modules that you
   want to use. For this first define CUSTOM_SETTINGS followed by defining
   INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/internet-module/
*/
#define CUSTOM_SETTINGS
#define INCLUDE_INTERNET_MODULE
#include <evive.h>
#include <Dabble.h>
String WRITE_KEY = "IXPXC82OLNNH1EBW";   //enter your thingspeak channel write key   


void setup() {
  Dabble.begin(115200); //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
  pinMode(TACTILESW1,INPUT);
}

void loop() {
  Dabble.processInput(); //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  if(digitalRead(TACTILESW1) == HIGH)
  {
    Internet.updateThingspeakField(WRITE_KEY, 1, analogRead(POT1));  //Thingspeak Write Key, Field number, Data
    Dabble.delay(500);   //Debounce delay
  }
}
