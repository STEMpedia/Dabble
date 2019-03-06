/* 
   Data Logger module helps you in storing data in form of .csv file. 
   Later you can open this file to view your stored data.
   
   You can reduce the size of library compiled by enabling only those modules that you want to
   use.For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/
*/   
#define CUSTOM_SETTINGS
#define INCLUDE_DATALOGGER_MODULE
#include <evive.h>
#include <Dabble.h>
bool isFileOpen = true; 
void initializeFile()
{
  DataLogger.createFile("Potentiometer3 Data");    //create file  (This is a mandatory step)
  DataLogger.createColumn("POT-1");               //enter column names (This is a mandatory step)
  DataLogger.createColumn("POT-2");              
}
void setup() {
  Serial.begin(250000);        //change baud rate of serial monitor to this baud
  Dabble.begin(115200);        //enter baudrate of your bluetooth
  pinMode(SLIDESW1_D1,INPUT);
  pinMode(TACTILESW1,INPUT);
  DataLogger.sendSettings(&initializeFile);    //callback function executed when bluetooth is connected  
}

void loop() {
  Dabble.processInput();  //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  if ((digitalRead(SLIDESW1_D1) == HIGH)  && isFileOpen == true)    //Move Slide Switch up to start data logging.
  {
    DataLogger.send("POT-1", analogRead(POT1));        //format to send data is to enter (column name,data)
    DataLogger.send("POT-2", analogRead(POT2));
    //delay(20);
  }
  if((digitalRead(TACTILESW1) == HIGH) && isFileOpen == true)  //press tactile switch once to close current data logger file
  {  
    DataLogger.close();                      //to close file created
    isFileOpen = false;
  }
}
