/*
   This example demonstrates how to use Notification module of Dabble app. Here status of touch sensors of evive is notified to mobile.
   
   You can reduce the size of library compiled by enabling only those modules that you
   want to use. For this first define CUSTOM_SETTINGS followed by defining
   INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/
*/
#define CUSTOM_SETTINGS
#define INCLUDE_NOTIFICATION_MODULE
#include <evive.h>
#include <Dabble.h>
bool isTouchSensed = false; 
void setup() {
  Serial.begin(250000);             // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(115200);             //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
  Dabble.waitForAppConnection();    //waiting for App to connect
  Notification.clear();             //clear previous notifictions
  Notification.setTitle("Touch sensor Status");      //Enter title of your notification
  touchPins.begin(0x5A);
}

void loop()
{
  Dabble.processInput();        //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  for (int i = 1; i <= 12; i++)
  {
    if (touchPins.isTouched(i))
    {
      isTouchSensed = true;
      Notification.notifyPhone(String("Touch is sensed on pin ") + i);              //Content of notification 
    }
  }    
  if(isTouchSensed == false)
  {
    Notification.notifyPhone("No touch was sensed by any touch pin");     //Content of notification
  }
  isTouchSensed = false;
}