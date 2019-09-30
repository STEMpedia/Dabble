#define FROM_DABBLE_LIBRARY
#include "Dabble.h"
#include "HardwareSerial.h"
#include "stdarg.h"
#include "SoftwareSerial.h"


#if(defined(__AVR_ATmega328P__))
SoftwareSerial DabbleSoftSerial;    
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
//byte DabbleClass::requestsCounter=0;
//HttpRequest ** DabbleClass::requestsArray=0;
// #endif

uint8_t FrameLimits[4][18] = {{0, 1,  2,  3, 4, 5, 6, 7, 8, 9, 10,  11,   12,  13,   14, 15, 16,  17},          //Module-ID
	                          {3, 3,  2,  3, 9, 4, 2, 0, 2, 3,  3,   4,    6,   5,    3,  5, 5,    3},          //Funtcion_ID
                              {1, 1,255,  1, 3, 1, 1, 0, 2, 1,  1,  26,    2,   1,    1, 10, 10, 255},          //Arg1
                              {5, 2,255, 32, 4, 2, 1, 0, 4, 2,  1,   3,   50, 255,    1, 10, 10, 255}};         //Arg2


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
	/*#ifdef DEBUG
	Serial.println("Waiting...");
	#endif*/
	//Serial.println("Waiting...");
    Dabble.processInput();
  }

}

void DabbleClass::init()
{
  isInit=true;
  sendModuleFrame(Dabble_ID,0,CHECK_CONNECTION,0);
  /*if(requestsArray!=0){
    for(int i=0;i<requestsCounter;i++)
      requestsArray[i]->sendInitFrame();
    free(requestsArray);
    requestsCounter=0;
  }*/
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
/*void DabbleClass::addToUnSentRequestsArray(HttpRequest * request)
{
  if(requestsCounter==MAX_NO_OF_REQUESTS) return;
  if(requestsCounter<=0)
    requestsArray=(HttpRequest**)malloc(sizeof(HttpRequest*)*MAX_NO_OF_REQUESTS);
  requestsArray[requestsCounter++] = request;  
}*/
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
  if (data == -1)
  {
    return;
  }
  if((millis() - argumentDataBytesTimeReceived) > 2000 && argumentDataBytesTimeReceived !=0 && framestart) 
  {
		freeMemoryAllocated();
  }
  argumentDataBytesTimeReceived = millis();
  #ifdef DEBUG
  Serial.println("counter " + String(counter));
  #endif
  if ((counter == 1) && framestart)
  {
    #ifdef DEBUG
	Serial.print("C2- ");
    #endif
	Module = data;
    if (Module > MODULE_NO - 1)
    {
      #ifdef DEBUG
	  Serial.println("WrongModule");
      #endif
	  return;
    }
    counter++;
  }
  else if ((counter == 2) && framestart)
  {
    #ifdef DEBUG
	Serial.print("C3- ");
    #endif
	functions = data;
    if (functions > FrameLimits[1][Module])
    {
      #ifdef DEBUG
	  Serial.println("Wrongfunctions");
      #endif
	  return;
    }
    counter++;
  }
  else if ((counter == 3) && framestart)
  {
    #ifdef DEBUG
	Serial.print("C4- ");
    #endif
	if (data > FrameLimits[2][Module])
    {
      #ifdef DEBUG
	  Serial.println("WrongArgId");
      #endif
	  return;
    }
    argumentnumber = data;
    if (argumentnumber != 0)
    {
      argumentL = new byte[argumentnumber];
      arguments = new byte*[argumentnumber];
    }// argumentL = (byte*) malloc(sizeof(byte) * argumentnumber);
    // arguments = (byte**)malloc(sizeof(byte) * argumentnumber);
    isArgumentLengthMalloced = 1;
    counter++;
  }
  else if ((counter == 4) && framestart)
  {
	#ifdef DEBUG  
    Serial.print("C5- ");
    #endif
	if (data == 0)
    {
      //Serial.println(counter);
      counter = 6;
      return;
      //Serial.println(counter);
    }
    if (data > FrameLimits[3][Module])
    {
      #ifdef DEBUG
	  Serial.println("WrongArg2Id");
      #endif
	  freeMemoryAllocated();
      return;
    }
    argumentL[argumentcounter] = data;
    // arguments[argumentcounter] = (byte*)malloc(sizeof(byte) * (argumentL[argumentcounter]));
    arguments[argumentcounter] = new byte[argumentL[argumentcounter]];
    isArgumentsNumberMalloced = 1;
    counter++;
  }
  else if ((counter == 5) && framestart)
  {
    #ifdef DEBUG
	Serial.print("C6- ");
    #endif
	if (datalengthcounter < argumentL[argumentcounter])
    {
      arguments[argumentcounter][datalengthcounter] = data;
      datalengthcounter++;
    }
    if (datalengthcounter == argumentL[argumentcounter])
    {
      counter = 4;
      datalengthcounter = 0;
      argumentcounter++;
    }
    if (argumentcounter == argumentnumber)
    {
      counter = 6;
    }
    //  Serial.println("datalengthcounter" + String(datalengthcounter));
    // Serial.println("currentArgNumber" + String(argumentcounter));
  }
  else if (counter == 6 && framestart)
  {
	#ifdef DEBUG  
    Serial.print("C7- ");
    #endif
	if (data == END_OF_FRAME)
    {
	  #ifdef DEBUG	
      Serial.println("EndFrame");
      #endif
	  sendToModules();
	  counter = 0;
      framestart = 0;
      freeMemoryAllocated();
	}
  }
  else if (counter == 0 && data == START_OF_FRAME)
  {
    datalengthcounter = 0;
    argumentcounter = 0;
    argumentnumber = 0;
    framestart = 1;
    counter++;
    #ifdef DEBUG
	Serial.print("C1- ");
	#endif
  }
  #ifdef DEBUG
  Serial.print(data);
  Serial.print("  ");
  #endif
}

void DabbleClass::processInput()
{

    if(DabbleSerial->available())
	{
      	isDabbleConnected = true;
	  while(DabbleSerial->available())
     {
        	//Serial.println("In processInput");
			
		byte data=DabbleSerial->read();
		processInput(data);
		
     }
    }
}

void DabbleClass::freeMemoryAllocated(){
  if (isArgumentsNumberMalloced == 1)
  {
    for (int i = 0; i < argumentcounter; i++)
    {
      #ifdef DEBUG
	  Serial.print("F3");
      #endif
	  //free(arguments[i]);
      delete [] arguments[i];
    }
    //free(arguments);
    delete [] arguments;
  }
  #ifdef DEBUG
  Serial.print("F1");
  #endif
  //free(argumentL);
  if (isArgumentLengthMalloced == 1)
  {
    delete [] argumentL;
  }
  isArgumentLengthMalloced = 0;
  isArgumentsNumberMalloced = 0;
  #ifdef DEBUG
  Serial.println("F2");
  #endif
  datalengthcounter = 0;
  argumentcounter = 0;
  argumentnumber = 0;
  arguments = NULL;
  argumentL = NULL;
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
      uint8_t BoardId_Mega[4] = {0x02,1,5,1};
	  uint8_t BoardId_Uno[4] =  {0x03,1,5,2};
	  uint8_t BoardId_Nano[4] = {0x04,1,5,2};
	  uint8_t BoardId_Other[4] = {0x05,1,5,2};
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
DabbleClass Dabble;
