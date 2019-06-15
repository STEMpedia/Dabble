#ifndef InternetModule_h
#define InternetModule_h

#include "ModuleParent.h"

#include "CircularBuffer.h"

//Function-Id
#define HTTP_GET 0x01
#define HTTP_SUCCESS 0x02
#define HTTP_RESPONSE 0x03	


class InternetModule :public ModuleParent
{
public:
	//Constructor
	InternetModule();
	void sendGETRequest(String);
	void updateThingspeakChannel(String KEY,int noOfData, int value1=0, int value2=0, int value3=0, int value4=0, int value5=0, int value6=0, int value7=0, int value8=0);
	void updateThingspeakChannel(String KEY,int noOfData, String value1="", String value2="", String value3="", String value4="", String value5="", String value6="", String value7="", String value8="");
	void updateThingspeakField(String KEY,uint8_t fieldNumber,int data);
    void updateThingspeakField(String KEY,uint8_t fieldNumber,String data);
	
	//float getFieldData(String KEY,uint8_t fieldNumber,long timeout=10000);
	//void getWeatherData(String KEY, float Lat, float Lon);
	//float getLatitude();
	//float getLongitude();
	//float getTemperatureK();
	//float getTemperatureC();
	//float getTemperatureF();
	//float getHumidity();
	//float getPressure();
	//float getWeatherValueFloat(int feild);
	//String getWeatherValueString(int feild);
	
private:
    String mainString = "";
	bool successState= 0;
	void processData();
	/*float latitude;
	float longitude;
	float temperatureK;
	float temperatureC;
	float temperatureF;
	float humidity;
	float pressure;
	float visibility;
	float windSpeed;
	float windDirection;
	float cloud;
	float rain1hr;
	float dataTime;
	float sunRiseTime;
	float sunSetTime;
	String weather = String();
	String weatherDescription = String();
	String countryCode = String();
	String cityName = String();
	String dataTimeString = String();
	String sunRiseTimeString = String();
	String sunSetTimeString = String();	*/
};
//Extern Object
extern InternetModule Internet;
#endif