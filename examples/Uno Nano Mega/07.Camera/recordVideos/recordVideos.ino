/*
  Camera Module allows you to click images and videos from smartphone by sending commands from your evive.
  This function demonstrates functions available in library for camera module. 

  Open Serial monitor and follow the instructions printed there to take images and videos in different cases.

  NOTE:
   1)For Arduino Mega Connect Bluetooth on Serial3 pins.
   2)For Arduino Uno/Nano library uses SoftwareSerial,hence pin 2 and pin 3 are used
   as RX and TX pins respectively on SoftwareSerial.Hence with arduino Uno
   follow below connections for bluetooth.
   UNO  - BLUETOOTH
   2    - TX
   3    - RX
   3)For Uno/Nano keep bluetooth Baudrate below 38400.

   You can reduce the size of library compiled by enabling only those modules that you want
   to use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/
*/
#define CUSTOM_SETTINGS
#define INCLUDE_CAMERA_MODULE

#include <Dabble.h>

void setup() {
  Serial.begin(250000);
  Dabble.begin(9600);
  printMessage();
}

void loop() {
  Dabble.processInput();
  char a = processSerialdata();
  if( a == '1')
  {
    Camera.setParameters(Front,Off,High,0);  //Direction , Flash, Quality, zoom(0-100%)
    Camera.captureImage();
    Camera.startRecording();
  }
  if( a == '2')
  {
    Camera.flipTo(Rear);
    Camera.flashMode(Auto);
    Camera.setQuality(Low);
    Camera.startRecording();
  }
  if(a == '3')
  {
    Camera.flipTo(Rear);
    Camera.setQuality(High);
    Camera.zoom(50);
    Camera.captureImage();
    Camera.startRecording();
  }

  if(a == '4')
  {
    Camera.stopRecording();
  }
 

}

void printMessage()
{
  Serial.println("Enter any number between 1 to 4 for executing task corresponding to that number: ");
  Serial.println("Tasks executed on sending different numbers are as followed: ");
  Serial.println("1 - Take a high quality video from front camera with no flash and no zoom.");
  Serial.println("2 - Take a video from rear camera with Auto flash");
  Serial.println("3 - Take a 50% zoomed image from Rear camera with high quality"); 
  Serial.println("4 - Stop video recording");
}

char processSerialdata()
{
  if(Serial.available()!=0)
  {
   return Serial.read(); 
  }
  else
  {
    return '0';
  }
}

