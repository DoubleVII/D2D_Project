#include <dsound.h>


#pragma once
class GameSound
{
public:
	GameSound(LPDIRECTSOUNDBUFFER* sounds ,int size);
	virtual ~GameSound();
	void play();


private:
	LPDIRECTSOUNDBUFFER* sounds;
	int size;
	int pointer;
};

