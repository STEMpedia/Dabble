#ifndef PinMonitorModule_h
#define PinMonitorModule_h

#include "ModuleParent.h"
#include "Arduino.h"
#include "SoftwareSerial.h"


class PinMonitorModule : public ModuleParent
{ 
    byte* digitaldata=NULL;
    byte* analog_data=NULL;	
	public:
	#if defined(ARDUINO_AVR_MEGA2560)
	//byte byte_pins[6];
	byte function_id_d=0x01;
	byte function_id_a=0x03;
	uint8_t n=6; 
	uint8_t m=32;
	uint8_t digital_pins[6][8]={{2,3,4,5,6,7,8,9},{10,11,12,13},{22,23,24,25,26,27,28,29},{30,31,32,33,34,35,36,37}
	                      ,{38,39,40,41,42,43,44,45},{46,47,48,49,50,51,52,53}};
	uint8_t analog_pin[16]={A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15};
	//uint8_t analog_data[32];
    #endif
	
	#if defined(ARDUINO_AVR_UNO)
	//byte byte_pins[2];
	byte function_id_d = 0x02;
	byte function_id_a= 0x04;
	uint8_t n=2;
	uint8_t m=12;
   	uint8_t digital_pins[2][8]={{2,3,4,5,6,7,8,9},{10,11,12,13}};
	uint8_t analog_pin[6]={A0,A1,A2,A3,A4,A5};
    //uint8_t analog_data[12];
	#endif
	
	#if defined(ARDUINO_AVR_NANO)
	//byte byte_pins[2];
	byte function_id_d = 0x02;
	byte function_id_a= 0x04;
	uint8_t n=2;
	uint8_t m=16;
   	uint8_t digital_pins[2][8]={{2,3,4,5,6,7,8,9},{10,11,12,13}};
	uint8_t analog_pin[8]={A0,A1,A2,A3,A4,A5,A6,A7};
    //uint8_t analog_data[12];
	#endif
	
	public:
	PinMonitorModule();
	
	void sendDigitalData();
	void sendAnalogData();

	private:
	void processData();
    	
};

extern PinMonitorModule PinMonitor;
#endif