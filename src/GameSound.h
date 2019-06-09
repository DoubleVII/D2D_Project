#include <dsound.h>


#pragma once
class GameSound
{
public:
	GameSound(LPDIRECTSOUNDBUFFER* sounds ,int size);
	virtual ~GameSound();
	void play();
	void stop();


private:
	LPDIRECTSOUNDBUFFER* sounds;
	int size;
	int pointer;
};

