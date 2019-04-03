/* SMS module uses your smartphone to send SMS based on events occuring in your hardware board.
   
   You can reduce the size of library compiled by enabling only those modules that you
   want to use. For this first define CUSTOM_SETTINGS followed by defining
   INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/
*/
#define CUSTOM_SETTINGS
#define INCLUDE_SMS_MODULE

#include <evive.h>
#include <Dabble.h>

void setup() {
  Serial.begin(250000);     // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(115200);     //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
  pinMode(TACTILESW1, INPUT);
}

void loop() {
  Dabble.processInput();        //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  if(digitalRead(TACTILESW1) == HIGH)
  {
    SMS.sendMessage("1234567890","This is a test message from Dabble");     // Contact Number, Message Content
  }
}
