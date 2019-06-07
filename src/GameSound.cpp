#include "GameSound.h"
#include <assert.h>


GameSound::GameSound(LPDIRECTSOUNDBUFFER* sounds, int size) :
	sounds(sounds), size(size), pointer(0)
{
	assert(size > 0);
}



GameSound::~GameSound()
{
	for (int i = 0; i < size; ++i) {
		sounds[i]->Release();
	}
	delete[] sounds;
}

void GameSound::play()
{
	pointer = (pointer + 1) % size;
	sounds[pointer]->Play(0,0,0);
}
