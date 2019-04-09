#ifndef OscilloscopeModule_h
#define OscilloscopeModule_h
#include "Stream.h"
#include "Arduino.h"

union FloatToBytes {
  float floatNumber;
  byte floatToBytes[sizeof(float)];
};
class OscilloscopeModule
{
public:
	OscilloscopeModule();
	void begin(Stream &s);
  void sendDataChannel1(float);
	void sendDataChannel2(float);
private:
	static Stream * OscilloscopeSerial;
};
extern OscilloscopeModule Oscilloscope;
#endif
