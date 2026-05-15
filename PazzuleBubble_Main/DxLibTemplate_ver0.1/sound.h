#ifndef __SOUND_H__
#define __SOUND_H__

#pragma once

#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include"const.h"

struct SoundInfo
{

	int soundHandle;

	const char* soundPath;
};

class SoundManager
{
private:
	SoundManager();
	SoundManager& operator = (SoundManager& other) = delete;
	SoundManager(const SoundManager& other) = delete;
	SoundInfo soundInfoArray[SOUND_INFO_LENGTH];

public:
	enum SOUNDNAME
	{
		SOUND_SHOT = 0,
		SOUND_ADSORPTION,
		SOUND_BURST,
		SOUND_FALL,
		SOUND_STAGE,
	};

	static SoundManager* getInstance();

	void initSoundManager();
	bool setSoundInfo(int soundId, const char* soundPath);
	void loadSoundAll();
	int getSoundHandle(int soundId);
	void clearSoundManager();
	void setSoundVolume(int volume);
};



#endif


#endif

