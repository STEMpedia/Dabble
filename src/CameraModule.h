#ifndef CameraModule_h
#define CameraModule_h
#include "ModuleParent.h"

#define Rear   0x05
#define Front  0x04

#define On     0x06
#define Off    0x08
#define Auto   0x07

#define High 0x09 
#define Low  0x0A
 


class CameraModule:public ModuleParent
{
public:
CameraModule();
void setParameters(uint8_t,uint8_t,uint8_t,uint8_t);  //Direction,flash,quality,zoom
void captureImage();      //Camera Direction
void startRecording();    
//void startRecording(unsigned long);
void stopRecording();
void flashMode(byte);      //On, Off, Auto
void setQuality(uint8_t);   //High, Low
void zoom(uint8_t);         // enter zoom in % from 1 to 100.
void flipTo(uint8_t);
private:
uint8_t captureimage = 0x01;
uint8_t startVideo = 0x02;
uint8_t stopVideo  = 0x03;
};
extern CameraModule Camera;
#endif
