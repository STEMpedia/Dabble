/*
   Camera Module allows you to click images and videos from smartphone by sending commands from your evive.
   This function demonstrates all the functions available in library for camera module.

   You can reduce the size of library compiled by enabling only those modules that you want to
   use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/
*/
#define CUSTOM_SETTINGS
#define INCLUDE_CAMERA_MODULE
#include <evive.h>
#include <Dabble.h>
void setup() {
  Serial.begin(250000);   // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(115200);   //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
}

void loop() {
  Dabble.processInput();     //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  if (digitalRead(TACTILESW1) == HIGH)
  {
    Camera.setParameters(FRONT, OFF, HIGH_QUALITY, 0);   //Direction of camera, Flash Mode, Quality, zoom
    Camera.captureImage();
    while (digitalRead(TACTILESW1) == HIGH);     //to prevent execution of task multiple times for single press on Tactile switch.
    delay(100);                                  //debounce delay
  }


  if (digitalRead(TACTILESW2) == HIGH)
  {
    Camera.flipTo(REAR);   //Since here only direction of camera changed hence all other parameters like Flash mode, Quality and zoom remains same as per previous declarations or default
    Camera.zoom(50);       //Take a 50% zoomed image
    Camera.captureImage();
    while (digitalRead(TACTILESW2) == HIGH); //to prevent execution of task multiple times for single press on Tactile switch.
    delay(100);                              //debounce delay
  }
}



