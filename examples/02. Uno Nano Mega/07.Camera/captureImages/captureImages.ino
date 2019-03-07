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
  Serial.begin(9600);       // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);       //Change this baudrate as per your bluetooth baudrate. Connect bluetooth on digital pin 2(RX) and 3(TX) for Uno/Nano and on Serial3 pins for Mega.
  printMessage();
}

void loop() {
  Dabble.processInput();  //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  char a = processSerialdata();
  if( a == '1')
  {
    Camera.setParameters(FRONT,OFF,HIGH_QUALITY,0);   //Camera Direction, Flash, quality, Zoom(from 0 to 100%)
    Camera.captureImage();
  }
  if( a == '2')
  {
    Camera.flipTo(REAR);
    Camera.flashMode(OFF);
    Camera.setQuality(LOW_QUALITY);
    Camera.captureImage();
  }
  if(a == '3')
  {
    Camera.flipTo(REAR);
    Camera.setQuality(HIGH_QUALITY);
    Camera.zoom(50);
    Camera.captureImage();
  }
 

}

void printMessage()
{
  Serial.println("Enter any number between 1 to 3 for executing task corresponding to that number: ");
  Serial.println("Tasks executed on sending different numbers are as followed: ");
  Serial.println("1 - Take a high quality image from front camera with no flash and no zoom.");
  Serial.println("2 - Take a low quality image from rear camera with Off flash and no zoom");
  Serial.println("3 - Take a 50% zoomed image from Rear camera with high quality"); 
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

