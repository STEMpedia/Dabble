/*
   Color detector module process live actions viewed by camera and gives color as per selected settings.
  
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

   This code helps you in identifying basic colors namely red, blue, green, yellow and violet.
   The method present in the library allows you to differentiate only these 5 colors.
   Explore more on: https://thestempedia.com/docs/dabble/
*/
#define CUSTOM_SETTINGS
#define INCLUDE_COLORDETECTOR_MODULE
#include <Dabble.h>

void initialSetup()
{
  ColorDetector.setGridSize(GRID_1x1);
  ColorDetector.setCalculationMode(DOMINANT);
  ColorDetector.setColorScheme(RGB_24BIT);
}
//to store red, green and blue color component values
int color[3] = {-1, -1, -1};  //store data in this array in R,G,B sequence. All three color components initialised to -1. 
void setup() {
  Serial.begin(9600);  // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);  //Change this baudrate as per your bluetooth baudrate. Connect bluetooth on digital pin 2(RX) and 3(TX) for Uno/Nano and on Serial3 pins for Mega.
  ColorDetector.sendSettings(&initialSetup);  
}

void loop() {
  Dabble.processInput();  //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  //Store color components
  color[0] = ColorDetector.getRedColor();   
  color[1] = ColorDetector.getGreenColor();
  color[2] = ColorDetector.getBlueColor();
  Serial.print("Color Found: ");
  if(ColorDetector.checkColor(color,RED) == 1)
  {
    Serial.println("Red");
  }
  else if(ColorDetector.checkColor(color,GREEN) == 1)
  {
    Serial.println("Green");
  }
  else if(ColorDetector.checkColor(color,BLUE) == 1)
  {
    Serial.println("Blue");
  }
  else if(ColorDetector.checkColor(color,YELLOW) == 1)
  {
    Serial.println("Yellow");
  }else if(ColorDetector.checkColor(color,VIOLET) == 1)
  {
    Serial.println("Violet");
  }
  else{
    Serial.println("None");
  }
}
