#define FROM_DABBLE_LIBRARY
#include "Dabble.h"
#include "CameraModule.h"

CameraModule::CameraModule(): ModuleParent(CAMERA_ID)
{
	
}

void CameraModule::CaptureImage()
{
	 Dabble.sendModuleFrame(CAMERA_ID,0,0x01,1,new FunctionArg(1,imageCapture));
}

void CameraModule::CameraFlip()
{
	Dabble.sendModuleFrame(CAMERA_ID,0,0x01,1,new FunctionArg(1,FlipCamera));
}

void CameraModule::CaptureVideo()
{
	Dabble.sendModuleFrame(CAMERA_ID,0,0x01,1,new FunctionArg(1,videoCapture));
}

void CameraModule::FlashToggle()
{
	Dabble.sendModuleFrame(CAMERA_ID,0,0x01,1,new FunctionArg(1,ToggleFlash));
}

/* void CameraModule::processData(){
	
} */