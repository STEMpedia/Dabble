#define FROM_DABBLE_LIBRARY
#include "Dabble.h"
#include "MusicModule.h"

MusicModule::MusicModule():ModuleParent(MUSIC_ID)
{}

void MusicModule::play(String name){
	Dabble.sendModuleFrame(MUSIC_ID,0,PLAYNOW,1, new FunctionArg(name.length(), (byte *)(&name[0])));
}

void MusicModule::addToQueue(String name){
	Dabble.sendModuleFrame(MUSIC_ID,0,ADDTOQUEUE,1, new FunctionArg(name.length(), (byte *)(&name[0])));
}

void MusicModule::stop(){
	Dabble.sendModuleFrame(MUSIC_ID,0,STOPMUSIC,0);
}

	void MusicModule::playMusic(uint8_t a,String key){
	if(a==1)
	{
		play(key);
	}
	if(a==1)
	{
		addToQueue(key);
	}
}