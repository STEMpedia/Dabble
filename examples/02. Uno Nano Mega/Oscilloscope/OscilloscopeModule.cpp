#include "OscilloscopeModule.h"
Stream * OscilloscopeModule::OscilloscopeSerial = 0;
OscilloscopeModule::OscilloscopeModule()
{
}

void OscilloscopeModule::begin(Stream &s)
{
	OscilloscopeSerial = &s;
	while(OscilloscopeSerial->available() == 0);
	while(OscilloscopeSerial->available() !=0)
	{
		OscilloscopeSerial->read();
	}
	OscilloscopeSerial->write(0xFF);
	OscilloscopeSerial->write(0x08);
}

void OscilloscopeModule::sendDataChannel1(float a)
{
	FloatToBytes floatToBytesChannel1;
	floatToBytesChannel1.floatNumber = a;
	OscilloscopeSerial->write(0x01);
	OscilloscopeSerial->write(floatToBytesChannel1.floatToBytes[0]);
	OscilloscopeSerial->write(floatToBytesChannel1.floatToBytes[1]);
	OscilloscopeSerial->write(floatToBytesChannel1.floatToBytes[2]);
	OscilloscopeSerial->write(floatToBytesChannel1.floatToBytes[3]);
	delay(2);
}
void OscilloscopeModule::sendDataChannel2(float a)
{
	FloatToBytes floatToBytesChannel2;
	floatToBytesChannel2.floatNumber = a;
	OscilloscopeSerial->write(0x02);
	OscilloscopeSerial->write(floatToBytesChannel2.floatToBytes[0]);
	OscilloscopeSerial->write(floatToBytesChannel2.floatToBytes[1]);
	OscilloscopeSerial->write(floatToBytesChannel2.floatToBytes[2]);
	OscilloscopeSerial->write(floatToBytesChannel2.floatToBytes[3]);
	delay(2);
}

OscilloscopeModule Oscilloscope;

