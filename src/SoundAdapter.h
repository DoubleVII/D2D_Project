#include <dsound.h>

#pragma comment(lib,"dsound.lib")


#pragma once
class SoundAdapter
{
public:
	SoundAdapter();
	virtual ~SoundAdapter();
	HRESULT DSound_Load_Wav(LPWSTR filename, int control_flags);
};

