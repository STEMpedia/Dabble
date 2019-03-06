#define FROM_DABBLE_LIBRARY
#include "Dabble.h"
#include "LedControlModule.h"

LedControlModule::LedControlModule(): ModuleParent(LEDCONTROL_ID)
{
}

void LedControlModule::processData()
{
  byte   functionId =getDabbleInstance().getFunctionId();
  
  if(functionId == 0x01)
  {
   value = getDabbleInstance().getArgumentData(0)[0]; 	
    if(value >13)
    {		
    #if(!(defined(__AVR_ATmega328P__)))
	pin = value;
    pinMode(pin,OUTPUT);
	analogWrite(pin,map(brightness,0,100,0,255));
	#endif
	}
	else
	{
	pin = value;
    pinMode(pin,OUTPUT);
	analogWrite(pin,brightness);
	}
  }
  else if (functionId == 0x03)    //ON as per Brightness value
  {
   value = getDabbleInstance().getArgumentData(0)[0]; 	  
   brightness = value;
   value  = map(value,0,100,0,255);
   analogWrite(pin,value);          //"value" always has value 255 for non PWM pins
  }
  else if(functionId == 0x02)         //OFF
  {
   brightness =0;
   digitalWrite(pin,LOW);
  }
}

uint8_t LedControlModule::readBrightness()
{
return brightness;
}

bool LedControlModule::getpinState()
{
 if(brightness>0)
 return 1; 
 else
 return 0;
}

uint8_t  LedControlModule::getpinNumber()
{
 return pin;
}

