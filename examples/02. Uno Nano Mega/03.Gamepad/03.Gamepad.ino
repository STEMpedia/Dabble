/*
    Gamepad module provides three different mode namely Digital, JoyStick and Accerleometer.
    NOTE:
    1)For Arduino Mega Connect Bluetooth on Serial3 pins.
    2)For Arduino Uno/Nano library uses SoftwareSerial,hence pin 2 and pin 3 are used
    as RX and TX pins respectively on SoftwareSerial.Hence with arduino Uno
    follow below connections for bluetooth.
    UNO  - BLUETOOTH
    2    - TX
    3    - RX
    3)For Uno/Nano keep bluetooth Baudrate below 38400.

    You can reduce the size of library compiled by enabling only those modules that you want to
    use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

    Explore more on: https://thestempedia.com/docs/dabble/game-pad-module/
*/

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);       // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);  //Change this baudrate as per your bluetooth baudrate. Connect bluetooth on digital pin 2(RX) and 3(TX) for Uno/Nano and on Serial3 pins for Mega.
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.      //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    Serial.print("UP");
  }

  if (GamePad.isDownPressed())
  {
    Serial.print("DOWN");
  }

  if (GamePad.isLeftPressed())
  {
    Serial.print("Left");
  }

  if (GamePad.isRightPressed())
  {
    Serial.print("Right");
  }

  if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
  }

  if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
  }

  if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");
  }

  if (GamePad.isTrianglePressed())
  {
    Serial.print("Triangle");
  }

  if (GamePad.isStartPressed())
  {
    Serial.print("Start");
  }

  if (GamePad.isSelectPressed())
  {
    Serial.print("Select");
  }
  Serial.print('\t');

  int a = GamePad.getAngle();
  Serial.print("Angle: ");
  Serial.print(a);
  Serial.print('\t');
  int b = GamePad.getRadius();
  Serial.print("Radius: ");
  Serial.print(b);
  Serial.print('\t');
  float c = GamePad.getx_axis();
  Serial.print("x_axis: ");
  Serial.print(c);
  Serial.print('\t');
  float d = GamePad.gety_axis();
  Serial.print("y_axis: ");
  Serial.println(d);
  Serial.println();
}
