/*
  This code demonstrates how to use music module. Here a push button is used for playing and stopping music in smartphone.
  A push button is connected on an internally pulled up digital pin. And a change in state of pin is read.
  With every press on push button state of music module will be toggled.If no music is played by music module then
  command to play music module will be sent and if currently music is being played then it will be stopped.

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

  Explore more on: https://thestempedia.com/docs/dabble/music-module/

*/
#define CUSTOM_SETTINGS
#define INCLUDE_MUSIC_MODULE
#include <Dabble.h>

bool playMusic = false;
uint8_t musicSignalPin = 5;
bool currentStatusOfPin = 0, prevStatusOfPin = 0; //status of musicSignalPin
bool musicIsOn = false;

void setup() {
  pinMode(musicSignalPin, INPUT_PULLUP);
  Dabble.begin(9600);  //Change this baudrate as per your bluetooth baudrate. Connect bluetooth on digital pin 2(RX) and 3(TX) for Uno/Nano and on Serial3 pins for Mega.
}

void loop() {
  Dabble.processInput(); //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  currentStatusOfPin = digitalRead(musicSignalPin);
  if (currentStatusOfPin == 0 &&  prevStatusOfPin == 1) //detecting change in state of pin due to push button
  {
    delay(500); // debouncedelay
    playMusic = !(playMusic);
  }
  if (playMusic == true)
  {
    if (musicIsOn == false)
    {
      Music.play("A4");         //assigned key for Piano Note A4
      Music.addToQueue("B4");   //assigned key for Piano Note B4
      Music.addToQueue("C4");   //assigned key for Piano Note C4
      Music.addToQueue("D4");   //assigned key for Piano Note D4
      Music.addToQueue("E4");   //assigned key for Piano Note E4
      Music.addToQueue("F4");   //assigned key for Piano Note F4
      Music.addToQueue("G4");   //assigned key for Piano Note G4
      Music.addToQueue("C5");   //assigned key for Piano Note C5   //Select your own music files, assign them key and write this key as written here for various piano notes.
      musicIsOn = true;
    }
  }
  if (playMusic == false)
  {
    Music.stop();
    musicIsOn = false;
  }
  prevStatusOfPin = currentStatusOfPin;
}

