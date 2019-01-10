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
  Serial.begin(250000);
  Dabble.begin(115200);
}

void loop() {
  Dabble.processInput();
  if (digitalRead(TACTILESW1) == 1)
  {
    Camera.setParameters(Front, Off, High, 0);   //Direction of camera, Flash Mode, Quality, zoom
    Camera.captureImage();
    while (digitalRead(TACTILESW1) == HIGH);     //to prevent execution of task multiple times for single press on Tactile switch.
  }


  if (digitalRead(TACTILESW2) == 1)
  {
    Camera.flipTo(Rear);   //Since here only direction of camera changed hence all other parameters like Flash mode, Quality and zoom remains same as per previous declarations or default
    Camera.zoom(50);       //Take a 50% zoomed image
    Camera.captureImage();
    while (digitalRead(TACTILESW2) == HIGH); //to prevent execution of task multiple times for single press on Tactile switch.
  }
}



