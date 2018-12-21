

#ifndef LedControlModule_h
#define LedControlModule_h

#include "ModuleParent.h"


class LedControlModule : public ModuleParent
{
	byte value;
    public:
	//Constructor
	LedControlModule();
	uint8_t readBrightness();
	bool   getpinState();
	uint8_t getpinNumber();
	uint8_t pin;
	uint8_t brightness;
    private:
	//Reserve Variables  

	//bool isCallBackAssigned;
	//Process Input Data  
	void processData();
	/*void (*buttonChangeCallBack)(unsigned char , unsigned char ,
								 unsigned char , unsigned char ,
								 unsigned char ,unsigned char  ,
								 unsigned char ,unsigned char );*/
};

//Extern Object
extern LedControlModule LedControl;
#endif 