/*
   Camera Module allows you to click images and videos from smartphone by sending commands from your evive.
   This function demonstrates the functions available in library for camera module.

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
  
  if (digitalRead(SLIDESW1_D1) == HIGH)
  {
    Camera.setParameters(Rear, Off, Low, 0);    //A low quality video capture from rear camera with Off flash
    Camera.startRecording();
    while (digitalRead(SLIDESW1_D1) == HIGH);  //to keep on video recording till the Slideswitch1 is in D1(UP) direction
    Camera.stopRecording();
  }
  
  
  if (digitalRead(SLIDESW1_D2) == HIGH)
  {
    Camera.flipTo(Front);              //To capture high quality video from front camera of your smartphone.
    Camera.setQuality(High);
    Camera.startRecording();
    while (digitalRead(SLIDESW1_D2) == HIGH); //to keep on video recording till the Slideswitch1 is in D2(Down) direction
    Camera.stopRecording();
  }
  
  
  if (digitalRead(SLIDESW2_D1) == HIGH)
  {
    Camera.flipTo(Rear);                   //Capture a video with auto flash mode from rear camera
    Camera.flashMode(Auto);
    Camera.startRecording();
    while (digitalRead(SLIDESW2_D1) == HIGH); //to keep on video recording till the Slideswitch2 is in D1(UP) direction
    Camera.stopRecording();
  }

  
  if (digitalRead(SLIDESW2_D2) == HIGH)
  {
    Camera.zoom(50);                       //Capture a 50% zoomed high quality video from rear camera
    Camera.flipTo(Rear);
    Camera.setQuality(High);
    Camera.startRecording();
    while (digitalRead(SLIDESW2_D2) == HIGH); //to keep on video recording till the Slideswitch2 is in D2(Down) direction
    Camera.stopRecording();
  }
}



