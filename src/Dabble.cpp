
#define FROM_DABBLE_LIBRARY
#include "Dabble.h"
#include "HardwareSerial.h"
#include "stdarg.h"
#include "SoftwareSerial.h"


#if(defined(__AVR_ATmega328P__))
SoftwareSerial DabbleSoftSerial;    //
#endif

bool callBackForDataLogger = false;
void (*dataLoggerCallBack)(void); 

 
bool DabbleClass::isInit=false;
bool DabbleClass::isSws=false;
byte DabbleClass::ModulesCounter=0;
unsigned long DabbleClass::lastTimeFrameSent=0;
unsigned long DabbleClass::argumentDataBytesTimeReceived=0;
bool DabbleClass::inACallback=false;
bool DabbleClass::callbacksInterrupts=false;
bool DabbleClass::isFirstFrame=false;
ModuleParent * DabbleClass::ModulesArray[]={0};
Stream * DabbleClass::DabbleSerial = 0;
// #ifdef INTERNET_Module
byte DabbleClass::requestsCounter=0;
HttpRequest ** DabbleClass::requestsArray=0;
// #endif
//Class Constructor
DabbleClass::DabbleClass()
{
      Module=0;
      verificationByte=0;
      functions=0;
      counter=0;
      argumentcounter=0;
      datalengthcounter=0;
      argumentnumber=0;
      endFrame=0;
      numberOfDataMalloced=0;
      isArgumentsNumberMalloced=false;
      isArgumentLengthMalloced=false;
      callbacksInterrupts=false;
      framestart =false;
      isDabbleConnected =false;
      isAppConnectionCallBack = false;
      isModuleFrameCallback = false;
      isSerialDataCallback = false;
      dontDelay = false;
	  
}

//Library Starter
void DabbleClass::begin(long baudRate,int rx,int tx)
{

	//Serial.println("In baud rate begin");
  #if(defined(__AVR_ATmega32U4__) || \
     defined(ARDUINO_LINUX) || \
     defined(__MK20DX128__) || \
     defined(__MK20DX256__) || \
     defined(__MKL26Z64__) || \
     defined(_VARIANT_ARDUINO_101_X_) || \
     defined(_VARIANT_ARDUINO_ZERO_))
     DabbleSerial=&Serial1;
     Serial1.begin(baudRate);
   #elif(defined(__AVR_ATmega2560__))
	 DabbleSerial=&Serial3;
     Serial3.begin(baudRate);
   #elif(defined(__AVR_ATmega328P__))
	 //Serial.println("UNO detected");
     DabbleSoftSerial.configure(rx,tx);
	 DabbleSerial=&DabbleSoftSerial;
	 DabbleSoftSerial.begin(baudRate);
	 //DabbleSerial=&Serial;
	 //Serial.begin(baudRate);
   #else
     DabbleSerial=&Serial;
     Serial.begin(baudRate);
   #endif
    if(!isInit){
    
    //isSws=true;
    init();
  }
   /* if(DabbleSerial==&DabbleSoftSerial)
	{
		Serial.println("DabbleSoftSerial initialized");
	}*/
}


//Blocking function 
void DabbleClass::waitForAppConnection()
{
  isDabbleConnected = false;

  while(!isDabbleConnected)
  {
    Dabble.processInput();
  }

}

void DabbleClass::init()
{
  isInit=true;
  sendModuleFrame(Dabble_ID,0,CHECK_CONNECTION,0);
  if(requestsArray!=0){
    for(int i=0;i<requestsCounter;i++)
      requestsArray[i]->sendInitFrame();
    free(requestsArray);
    requestsCounter=0;
  }
}

//Library Starter
void DabbleClass::begin()
{
if(!isInit){
	
    begin(115200);
    isSws=false;
    init();
  }
}

//Library Starter
void DabbleClass::begin(Stream &s)
{
  if(!isInit){
	 
    DabbleSerial=&s;
    //isSws=true;
    init();
  }
}

void DabbleClass::addToModulesArray(ModuleParent * Module)
{
  if(ModulesCounter==MODULE_NO) return;
  ModulesArray[ModulesCounter++] = Module;  
  
}
// #ifdef INTERNET_Module
void DabbleClass::addToUnSentRequestsArray(HttpRequest * request)
{
  if(requestsCounter==MAX_NO_OF_REQUESTS) return;
  if(requestsCounter<=0)
    requestsArray=(HttpRequest**)malloc(sizeof(HttpRequest*)*MAX_NO_OF_REQUESTS);
  requestsArray[requestsCounter++] = request;  
}
// #endif
bool DabbleClass::isInitialized()
{
  return isInit;
}

bool DabbleClass::isSoftwareSerial()
{
  return isSws;
}

void DabbleClass::setOnNewModuleFrame(void (*userFunction)(byte ModuleID, byte functionID, byte argNo,byte *argumentL,byte **arguments))
{
  isModuleFrameCallback=true;
  ModuleFrameCallback=userFunction;
}

void DabbleClass::setOnNewSerialData(void (*userFunction)(byte))
{
  isSerialDataCallback=true;
  serialDataCallback=userFunction;
}
void DabbleClass::appWrite(byte command)
{
  if(isInit){
		DabbleSerial->write(command);
		#ifdef DEBUG
		Serial.print(command);
		Serial.print(" ");
		#endif
	}
   if(!dontDelay)
  {
    ::delay(2);
  }
}

//Frame Sender for Output Modules
void DabbleClass::sendModuleFrame(byte ModuleID, byte instanceID, byte functionID, byte argNo, ...)
{
  unsigned long mill=millis()+1;
  unsigned long localLastTimeFrameSent=lastTimeFrameSent;
  if(ModuleID!=Dabble_ID&&isFirstFrame&&localLastTimeFrameSent&&(mill-localLastTimeFrameSent)<TIME_GAP){
  if(inACallback){
     DabbleClass TempDabble;
     ModuleParent::setDabbleInstance(TempDabble);
     while((millis()<(TIME_GAP+localLastTimeFrameSent))||TempDabble.framestart)
     {
        if(TempDabble.DabbleSerial->available())
          TempDabble.processInput(TempDabble.DabbleSerial->read());
     }
      ModuleParent::unSetDabbleInstance();
   }else
      while((millis()<(TIME_GAP+localLastTimeFrameSent))||framestart)
      {
        if(DabbleSerial->available())
          Dabble.processInput(DabbleSerial->read());
      }
  }

  isFirstFrame=true;
  va_list arguments ;
  va_start (arguments,argNo);
  appWrite((byte)START_OF_FRAME);
  //appWrite(LIBRARY_VERSION);
  appWrite(ModuleID);
  //appWrite(getVerificationByte());
  appWrite(functionID);
  appWrite(argNo);
  //appWrite(255-argNo);


  for (int i=0 ; i<argNo ; i++)
  {
    FunctionArg * temp = va_arg(arguments, FunctionArg *);
    appWrite(temp->getLength());
	
    //appWrite(255-(temp->getLength()));

      for (int j=0 ; j<temp->getLength() ; j++)
      {
        byte* tempData=temp->getData();
        appWrite(tempData[j]);
      }
    delete(temp);
  }
    appWrite((byte)END_OF_FRAME);
    va_end(arguments);
    if(ModuleID!=Dabble_ID)lastTimeFrameSent=millis()+1;
	#ifdef DEBUG
	Serial.println();
	#endif
}

void DabbleClass::sendModuleFrame(byte ModuleID, byte instanceID, byte functionID, byte argNo, FunctionArg ** arguments)
{
  unsigned long mill=millis()+1;
  unsigned long localLastTimeFrameSent=lastTimeFrameSent;
  if(ModuleID!=Dabble_ID&&isFirstFrame&&localLastTimeFrameSent&&(mill-localLastTimeFrameSent)<TIME_GAP){
  if(inACallback){
     DabbleClass TempDabble;
     ModuleParent::setDabbleInstance(TempDabble);
     while((millis()<(TIME_GAP+localLastTimeFrameSent))||TempDabble.framestart)
     {
        if(TempDabble.DabbleSerial->available())
          TempDabble.processInput(TempDabble.DabbleSerial->read());
     }
      ModuleParent::unSetDabbleInstance();
   }else
      while((millis()<(TIME_GAP+localLastTimeFrameSent))||framestart)
      {
        if(DabbleSerial->available())
          Dabble.processInput(DabbleSerial->read());
      }
  }

  isFirstFrame=true;
  appWrite((byte)START_OF_FRAME);
  //appWrite(LIBRARY_VERSION);
  appWrite(ModuleID);
  //appWrite(getVerificationByte());
  appWrite(functionID);
  appWrite(argNo);
  //appWrite(255-argNo);
  
  for (int i=0 ; i<argNo ; i++)
  {
    appWrite(arguments[i]->getLength());
    //appWrite(255-(arguments[i]->getLength()));
      for (int j=0 ; j<arguments[i]->getLength() ; j++)
      {
        byte* tempData=arguments[i]->getData();
        appWrite(tempData[j]);
      }
 }
    appWrite((byte)END_OF_FRAME);
    if(ModuleID!=Dabble_ID)lastTimeFrameSent=millis()+1;
	#ifdef DEBUG
	Serial.println();
	#endif
}
bool DabbleClass::isAppConnected()
{
  return isDabbleConnected;
}
void DabbleClass::setOnAppConnected(void (*userFunction)(bool isAppConnected))
{
  isAppConnectedCallBack = userFunction;
  isAppConnectionCallBack = true;
}
//Module_ID Getter
byte DabbleClass::getModuleId()
{
	return Module;
} 

//Funtcion_ID Getter
byte DabbleClass::getFunctionId()
{
  return functions;
}
//ArgumentsNumber Getter
byte DabbleClass::getArgumentNo()
{
  return argumentnumber;
} 
//ArgumentLength Getter
byte DabbleClass::getArgumentLength(byte x)
{
  return argumentL[x];
}
byte DabbleClass::getScreenId()
{
	return screenId;
	//if(getModuleId() == 0 && 
}

byte DabbleClass::readModuleId()
{
	return readModuleID;
}
//Data Getter
byte * DabbleClass::getArgumentData(byte x)
{
  if(argumentL[x]!=0)
    return arguments[x];
  else return NULL;
}

//Convert float to array of bytes
void DabbleClass::convertFloatToBytes(float data, byte * out)
{
  FloatUnion f2bUnion;
  f2bUnion.number = data;
  out[0]=f2bUnion.floatBytes[0];
  out[1]=f2bUnion.floatBytes[1];
  out[2]=f2bUnion.floatBytes[2];
  out[3]=f2bUnion.floatBytes[3];
 
} 

//Convert array of bytes to float
float DabbleClass::convertBytesToFloat(byte *data)
{
  FloatUnion b2fUnion;;
  b2fUnion.floatBytes[0] = data[0];
  b2fUnion.floatBytes[1] = data[1];
  b2fUnion.floatBytes[2] = data[2];
  b2fUnion.floatBytes[3] = data[3];
  return b2fUnion.number;
} 

//Incomming Frames processing 
void DabbleClass::processInput(int data) {
	#ifdef DEBUG
	Serial.print(data, HEX);
	Serial.print(" ");
	#endif
    
	if(data==-1){
		return;
	}
    if((millis() - argumentDataBytesTimeReceived) > 2000 && argumentDataBytesTimeReceived !=0 && framestart) 
      {
        freeMemoryAllocated();
      }
      argumentDataBytesTimeReceived = millis();
     if(!framestart&&data==START_OF_FRAME)
          {
              freeMemoryAllocated();
              counter=0;
              framestart=true;
              arguments=0;
              argumentL=0;
              counter++;
          }
          else if(counter==3&&framestart)                      //data is the no of arguments
          {
              #ifdef DEBUG
              Serial.print("C3 ");
              #endif
              datalengthcounter=0;
              argumentcounter=0;
              argumentnumber=data;
              //counter++;
          /* }
          else if(counter==5&&framestart)                      //data is the no of arguments
          {
              #ifdef DEBUG
              Serial.print("C5 ");
              #endif
              if((255-argumentnumber)==data&&argumentnumber==0){
                counter=9;
                return;
              }
              else if((255-argumentnumber)==data){ */
			  
			  if(argumentnumber != 0)
			  {
              arguments=(byte**)malloc(sizeof(byte*)*argumentnumber);//new byte*[argumentnumber];          //assigning the first dimension of the pointer (allocating dynamically space for 2d array)
              #ifdef DEBUG
              Serial.print("M1 ");
              #endif
              isArgumentsNumberMalloced=true;
              argumentL=(byte*)malloc(sizeof(byte)*argumentnumber);//new byte [argumentnumber];
              #ifdef DEBUG
              Serial.print("M2 ");
              #endif
              isArgumentLengthMalloced=true;
              }
			  counter++;
			  
              //}
/*               else{
                framestart=false;
                freeMemoryAllocated();
                return;
              } */
            }
          else if (counter==4&&framestart)                    // data is the first argument length
          {
              #ifdef DEBUG
              Serial.print("C4 ");
              #endif
              argumentL[argumentcounter]=data;
              //counter++;
          /* }
          else if (counter==7&&framestart)                    // data is the first argument Data information
          {
            #ifdef DEBUG
            Serial.print("C7 ");
            #endif
            if((255-argumentL[argumentcounter])==data){ */
			if(argumentnumber !=0)
			{
             if(argumentL[argumentcounter]!=0)                       //if(argumentL[argumentcounter]!=0)
              {
                arguments[argumentcounter]=(byte*)malloc(sizeof(byte)*argumentL[argumentcounter]); // assigning the second dimensional of the pointer
                #ifdef DEBUG
                Serial.print("M3 ");
                #endif
                counter++;
              }
              else
				 {	// Serial.print("ELSE ");
                arguments[argumentcounter]=NULL;
                datalengthcounter=0;
                argumentcounter++;
                if(argumentcounter==argumentnumber){
                  counter=6;
				  //Serial.print("ELSE ctr 6");
				}
                else{
                  counter=4;
				  //Serial.print("ELSE ctr 4");
				}
              }
			 }
			else
			{
				counter=6;
				//Serial.println("Argument number is 0");
			}
              numberOfDataMalloced++;
            //}
/*             else{
                framestart=false;
                freeMemoryAllocated();
                return;
              } */
          }
          else if (counter==5&&framestart)
          {
              #ifdef DEBUG
              Serial.print("C5 ");
              #endif
              if(arguments[argumentcounter]!=NULL)
			  arguments[argumentcounter][datalengthcounter++]=data;
              if (datalengthcounter==argumentL[argumentcounter])
              {
                  datalengthcounter=0;
                  argumentcounter++;
                  if(argumentcounter==argumentnumber)
                  {
                    counter++;                                    //increment the counter to take the last byte which is the end of the frame

                  }
                  else
                  {
                    counter=4;

                  }

              }

          }
          else if(counter==6&&framestart)
          {
              #ifdef DEBUG
              Serial.print("C6 ");
              #endif
            endFrame=data;
              if(endFrame==END_OF_FRAME)                                   //if the endframe is equal to zero send to Modules and free memory
              {
                      framestart=false;
					 // Serial.println("Sent to modules");
					 sendToModules();
					 if(isModuleFrameCallback && Module!=0)
                      {
                        enteringACallback();
                        ModuleFrameCallback(Module,functions,argumentnumber,argumentL,arguments);
                        exitingACallback();
                      }
                      freeMemoryAllocated();
					  #ifdef DEBUG
                      Serial.println();
					  #endif
              }
              else                                            //if endframe wasn't equal to zero make sure that the memory is free anyway
              {
                freeMemoryAllocated();
              }
          }
          else if(framestart){
                if(counter==1){
                  Module=data;
                  bool found = false;
                  if(Module == Dabble_ID || isModuleFrameCallback) found = true;
                  else 
				  { 
                  for (int i=0;i<ModulesCounter;i++) {
                    if (Module == ModulesArray[i]->getModuleId()){
                      found = true;
                        #ifdef DEBUG
						 Serial.print("Module: ");
						 Serial.print(Module, HEX);
						 Serial.print(" ");
						#endif
                    }
                   }
				  }
                  if (!found) {
                    framestart=false;
                    freeMemoryAllocated();
                    return;
                  }
                }
/*                 else if(counter==2){
                  verificationByte=data;
                  byte leastBits = verificationByte & 0x0F;
                  if(((255-verificationByte)>>4) != leastBits) framestart =false;
                  #ifdef DEBUG
                  Serial.print("C2 ");
                  #endif
                } */
                else if(counter==2){
                  functions=data;
                  #ifdef DEBUG
                  Serial.print("C2 ");
                  #endif
                }
            counter++;
          }

}

void DabbleClass::processInput()
{

	/*if(DabbleSerial == &DabbleSoftSerial)
	{
		Serial.println("myserial initials");
	}*/
	if(DabbleSerial->available())
	{
      while(DabbleSerial->available())
     {
      byte data=DabbleSerial->read();
	  #ifdef DEBUG
	  Serial.print(data);
	  Serial.print(" ");
      #endif	 
	 processInput(data);
     if(isSerialDataCallback)
     {
      enteringACallback();
      serialDataCallback(data);
      exitingACallback();
     }  
   }
   /*#ifdef DEBUG
   Serial.println();
   #endif*/
  }
}

void DabbleClass::freeMemoryAllocated(){
  framestart=false;
  if(isArgumentsNumberMalloced){
          for(int i=0;i<numberOfDataMalloced;i++)
          {
            if(arguments[i]!=NULL)free(arguments[i]);
            #ifdef DEBUG
            Serial.print("F3 ");
            #endif
          }
          numberOfDataMalloced=0;
          free(arguments);
          #ifdef DEBUG
          Serial.print("F1 ");
          #endif
          isArgumentsNumberMalloced=false;
        }
        if(isArgumentLengthMalloced){
          free(argumentL);
          #ifdef DEBUG
          Serial.println("F2 ");
          #endif
          isArgumentLengthMalloced=false;
        }
}

//Data Sender to Input Modules
void DabbleClass::sendToModules()
{
  //Checking the Module-ID    
  byte number_Of_Module= Dabble.getModuleId();  
 // Serial.println(Dabble.getArgumentData(0)[0]);  
  switch (number_Of_Module)
  {
    case Dabble_ID:processFrame();break;
    default:
    for(int i=0 ;i<ModulesCounter;i++)
    {
      ModulesArray[i]->processFrame();
    }
  }
}

void DabbleClass::processFrame(){
  byte functionId = getFunctionId();
  readModuleID = getArgumentData(0)[0];
  screenId = getArgumentData(0)[1];
  //Check  the function ID 
  if(functionId == BOARDID_REQUEST)
  {
	 // uint8_t BoardId_evive[1]={0x01};
      uint8_t BoardId_Mega[4] = {0x02,1,1,0};
	  uint8_t BoardId_Uno[4] =  {0x03,1,1,0};
	  uint8_t BoardId_Nano[4] = {0x04,1,1,0};
	  uint8_t BoardId_Other[4] = {0x05,1,1,0};
	  #if ((defined(ARDUINO_AVR_MEGA2560)) || (defined(ARDUINO_AVR_MEGA)))
	  sendModuleFrame(Dabble_ID,0,BOARDID_REQUEST,1,new FunctionArg(4,BoardId_Mega));
      #elif(defined(ARDUINO_AVR_NANO))
	  sendModuleFrame(Dabble_ID,0,BOARDID_REQUEST,1,new FunctionArg(4,BoardId_Nano));
      #elif(defined(ARDUINO_AVR_UNO))
	  sendModuleFrame(Dabble_ID,0,BOARDID_REQUEST,1,new FunctionArg(4,BoardId_Uno));
      #else
      sendModuleFrame(Dabble_ID,0,BOARDID_REQUEST,1,new FunctionArg(4,BoardId_Other));
      #endif  
	 /* #if (defined(__AVR_ATmega2560__))
	  sendModuleFrame(Dabble_ID,0,BOARDID_REQUEST,1,new FunctionArg(4,BoardId_Mega));
	  #elif (defined(__AVR_ATmega328P__))
	  sendModuleFrame(Dabble_ID,0,BOARDID_REQUEST,1,new FunctionArg(4,BoardId_Uno));
      #else
	  sendModuleFrame(Dabble_ID,0,BOARDID_REQUEST,1,new FunctionArg(4,BoardId_Other));
      #endif*/
 }
  if(callBackForDataLogger == true)
  {
	  callBackForDataLogger = false;
	 (*dataLoggerCallBack)(); 
  }
  /*else if(functionId == LIBRARY_VERSION_REQUEST)
  {
    sendModuleFrame(Dabble_ID,0,SEND_LIBRARY_VERSION,0);
  }
  else if(functionId == LIBRARY_TESTING_REQUEST)
  {
    if(!memcmp("Are you ok?",getArgumentData(0),11))
    {
      const char * responseString = "Yup, I'm feeling great!";
      byte testAnswer = 0;
      int sumOfData = 0;
      for(int i = 0 ; i < getArgumentLength(1) ; i++)
      {
        sumOfData+= getArgumentData(1)[i];
      }
      testAnswer = sumOfData%256;
      sendModuleFrame(Dabble_ID,0x00,LIBRARY_TESTING_RESPONSE,2,new FunctionArg(23,(byte *)responseString),new FunctionArg(1,&testAnswer));
    }
  }*/
}

//PulseWidthModulation Getter 
unsigned char DabbleClass::analogRead(int pin)
{
    double period=(double)pulseIn(pin,HIGH)+(double)pulseIn(pin,LOW);;
    double duty=(double)pulseIn(pin,HIGH);
    double fraction=duty/period;
    unsigned char pwm_out=(unsigned char)(ceil)(fraction*255);
    return pwm_out;
}

void DabbleClass::enteringACallback()
{
  if(!isInACallback())
  {
    inACallback=true;
    dontDelay = true;
    sendModuleFrame(Dabble_ID,0,CALLBACK_ENTERED,0);
    dontDelay = false;
  }
}

void DabbleClass::exitingACallback()
{
  if(isInACallback())
  {
    inACallback=false;
    dontDelay = true;
    sendModuleFrame(Dabble_ID,0,CALLBACK_EXITED,0);
    dontDelay = false;
  }
}

bool DabbleClass::isInACallback()
{
  return inACallback && !callbacksInterrupts;
}

bool DabbleClass::isCallbacksInterruptsSet()
{
  return callbacksInterrupts;
}

void DabbleClass::disableCallbacksInterrupts()
{
   callbacksInterrupts=false;
}

void DabbleClass::enableCallbacksInterrupts()
{
   callbacksInterrupts=true;
}

void DabbleClass::delay(unsigned long time)
{
  unsigned long now=millis();
    if(inACallback)
    {
     DabbleClass TempDabble;
     ModuleParent::setDabbleInstance(TempDabble);
     while((millis()<(now+time))||TempDabble.framestart)
     {
        if(TempDabble.DabbleSerial->available())
          TempDabble.processInput(TempDabble.DabbleSerial->read());
      }
      ModuleParent::unSetDabbleInstance();
   }else
      while((millis()<(now+time))||framestart)
      {
        if(DabbleSerial->available())
          Dabble.processInput(DabbleSerial->read());
      }
}
DabbleClass Dabble;
//Instantiating Object
/*#if (defined(__AVR_ATmega32U4__) || \
     defined(ARDUINO_LINUX) || \
     defined(__MK20DX128__) || \
     defined(__MK20DX256__) || \
	 defined(__MKL26Z64__) || \
     defined(_VARIANT_ARDUINO_101_X_) || \
     defined(_VARIANT_ARDUINO_ZERO_))
void serialEvent1()
#else
void serialEvent3()
#endif
{
  if(!Dabble.isSoftwareSerial()) Dabble.processInput();      
}*/

byte DabbleClass::getVerificationByte()
{
  byte randomValue = (byte)random(0,16);
  byte randomValueComplement = ~(randomValue);
  randomValue&=0x0F;
  randomValue = randomValue|(randomValueComplement<<4);
  return randomValue;
}
