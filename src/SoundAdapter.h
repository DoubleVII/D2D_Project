#include <dsound.h>
#include "GameSound.h"

#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"winmm.lib")

#ifndef DSBCAPS_CTRLDEFAULT
#define DSBCAPS_CTRLDEFAULT (DSBCAPS_CTRLFREQUENCY  | DSBCAPS_CTRLPAN  | DSBCAPS_CTRLVOLUME)
#endif

#pragma once
class SoundAdapter
{
public:
	SoundAdapter();

	bool Init(HWND main_window_handle);
	virtual ~SoundAdapter();
	HRESULT createSound(LPWSTR filename, GameSound** gameSound, int maxConcurrentNumber);

private:
	LPDIRECTSOUND lpds;
	HRESULT DSound_Load_Wav(LPWSTR filename, LPDIRECTSOUNDBUFFER* lpdbsBuffer_ptr, int maxConcurrentNumber, int control_flags = DSBCAPS_CTRLDEFAULT);
};

