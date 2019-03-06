/*
 * This code will help you in knowing your bluetooth baudrate and
 * will also help you in changing baudrate as per your requirements.
 * The most commonly used baudrate for HC-05 are 9600,38400,56700 and 115200.
 * To learn more about bluetooth module HC-05 refer the following link:
 * https://thestempedia.com/tutorials/bluetooth-setup/
 * 
 * For Uno/Nano you should keep your HC-05 baudrate below 38400 for its proper functioning.
 * 
 * 
 * Instructions:
 * In order to make the following code work you need to be sure that your bluetooth works in AT mode.
 * For entering AT mode follow these steps:
 * 1. Upload code to your board.
 * 2. Before powering bluetooth module press the push button on the module and keep it in pressed state.
 * 3. Now power the module (push button is still pressed.)
 * 4. You will see that LED on bluetooth module blinks one time in every 2 seconds approx.
 * 5. If you see this kind of blink you have successfully entered AT mode. If the blink is not as mentioned in step 3 
 *   then unplug bluetooth and follow procedure again.
 */

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);  // (RX,TX) connect  2 to TX of bluetooth and 3 to RX of bluetooth.
bool   response = 0;
String response_data = "";
String send_data="";
void setup() {
  Serial.begin(9600);
  mySerial.begin(38400);   
  checkATresponse();
  // put your setup code here, to run once:
}

void loop() {
  Serial.println("Enter 1 to read baudrate and 2 to write baudrate");
  while(Serial.available()==0);
  while(Serial.available()!=0)
  {
    uint8_t a=Serial.read();
    if(a == '1')
    {
      readBaudRate();
    }
    if(a == '2')
    {
      writeBaudRate(); 
    }
  }
}

void checkATresponse()
{
  long lastTime=0;
  while (!(response))
  {
    mySerial.print("AT\r\n");
    response_data = mySerial.readString();
    if (response_data != '\0')                
    {
    Serial.print("Command sent: "); 
    Serial.println("AT");
    Serial.print("Command received: ");
    Serial.println(response_data);
    response++;
    }
  }
  response=0;
}

void readBaudRate()
{
  while (!(response))
  {
    mySerial.print("AT+UART?\r\n");
    response_data = mySerial.readString();
    if (response_data != '\0')                
    {
    Serial.print("Command sent: ");   
    Serial.println("AT+UART?");
    Serial.print("Command received: ");
    Serial.println(response_data);
    response++;
    }
  }
  response=0;
}

void writeBaudRate()
{
  Serial.println("Enter any baudrate as per requirement. Some of the most commonly used baudrates are 9600,38400,56700 and 115200.\nHowever since we are using softwareSerial with Bluetooth keep baudrate below 38400.");
  Serial.println("Waiting for you to enter Baudrate...");
  while(Serial.available()==0);
  while(Serial.available()!=0)
  {
    send_data=Serial.readString();
    Serial.println(send_data);
  }
   while (!(response))
  {
    mySerial.print(String("AT+UART="+send_data+",0,0\r\n"));
    response_data = mySerial.readString();
    if (response_data != '\0')                
    {
    Serial.print("Command sent: ");   
    Serial.println(String("AT+UART="+send_data+",0,0"));
    Serial.print("Command received: ");
    Serial.print(response_data);
    response++;
    }
    if(response_data == "OK\r\n")
    {
      Serial.println("Baudrate changed successfully");
    }
    else
    {
      Serial.println("Error");
    }
  }
  response=0;
}

