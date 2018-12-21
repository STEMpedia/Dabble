
#ifndef DabbleInputs_h
#define DabbleInputs_h

#include "ModuleParent.h"

#define Potentiometer_1   0x01
#define Potentiometer_2   0x02
#define Switches          0x03
//#define DEBUG
class DabbleInputs: public ModuleParent
{
public:
	//Constructor
	DabbleInputs();
	//Checker Functions
	uint16_t getvalue_Pot1();
	uint16_t getvalue_Pot2();
	
	uint8_t getStatus_SlideSwitch1();
	uint8_t getStatus_SlideSwitch2();
	
	bool getStatus_TactileSwitch1();
	bool getStatus_TactileSwitch2();
	uint16_t getInputsData(uint8_t a);

public:
	byte functionId;
	
	byte data_1=0;
	byte data_2=0;
	byte data_3=0;
	byte data_4=0;
	byte data_5=0;
	uint8_t state_ss1;
    uint8_t state_ss2;
	
	
	
private:
	
	
	void processData();
};

//Extern Object
extern DabbleInputs Inputs;
#endif 