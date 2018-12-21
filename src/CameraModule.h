#ifndef CameraModule_h
#define CameraModule_h
#include "ModuleParent.h"

class CameraModule:public ModuleParent
{
	
public:
CameraModule();
void CaptureImage();
void CameraFlip();
void CaptureVideo();
void FlashToggle();

uint8_t imageCapture[1]={0x01};
uint8_t FlipCamera[1]={0x02};
uint8_t videoCapture[1]={0x03};
uint8_t ToggleFlash[1]={0x04};

private:
//processData();


};
extern CameraModule Camera;
#endif
