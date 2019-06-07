#include "SoundAdapter.h"

SoundAdapter::SoundAdapter():lpds(nullptr)
{
}

bool SoundAdapter::Init(HWND main_window_handle)
{
	if (DirectSoundCreate(NULL, &lpds, NULL) != DS_OK)
		return false;

	if (lpds->SetCooperativeLevel(main_window_handle, DSSCL_PRIORITY) != DS_OK)
		return false;
	return true;
}

SoundAdapter::~SoundAdapter()
{
}

HRESULT SoundAdapter::createSound(LPWSTR filename, GameSound** gameSound, int maxConcurrentNumber)
{
	HRESULT hr = S_OK;
	LPDIRECTSOUNDBUFFER* sounds = new LPDIRECTSOUNDBUFFER[maxConcurrentNumber];
	hr = DSound_Load_Wav(filename, sounds, maxConcurrentNumber);
	if (SUCCEEDED(hr)) {
		(*gameSound) = new GameSound(sounds, maxConcurrentNumber);
	}
	return hr;
}

//int GameInit(void* params, int num)
//{
//	LPDIRECTSOUNDBUFFER lpdbsBuffer_ptr;
//	//DSound_Load_Wav((LPWSTR)"Windows XP Startup.wav");
//
//	lpdbsBuffer_ptr->Play(0, 0, 1);
//	return 1;
//}
//-----------------------------------------------------------
//名称：DSound_Load_Wav
//功能：利用微软提供的mmio库，解析wav文件，将数据读入内存，然后拷贝到
//DirectSound建立的 辅助缓冲区 从而实现文件的播放（GameInit()）
//----------------------------------------------------------

HRESULT SoundAdapter::DSound_Load_Wav(LPWSTR filename, LPDIRECTSOUNDBUFFER* lpdbsBuffer_ptr, int maxConcurrentNumber, int control_flags)
{
	DSBUFFERDESC    dsbd;
	WAVEFORMATEX    wfmx;
	UCHAR* sndBuffer = NULL;
	HMMIO handle;
	MMCKINFO mmckriff, mmckIn;
	PCMWAVEFORMAT    pwfm;
	memset(&mmckriff, 0, sizeof(MMCKINFO));
	if ((handle = mmioOpen(filename, NULL, MMIO_READ | MMIO_ALLOCBUF)) == NULL)
		return S_FALSE;

	//--------------------------------------------
	//进入块(chunk),查找 riff和wave的标记
	//----------------------------------------------
	if (0 != mmioDescend(handle, &mmckriff, NULL, 0))
	{
		mmioClose(handle, 0);
		return S_FALSE;
	}

	//-----------------------------------------
	//#define FOURCC_RIFF  mmioFOURCC('R','I','F','F')
	//----------------------------------------------
	if (mmckriff.ckid != FOURCC_RIFF || mmckriff.fccType != mmioFOURCC('W', 'A', 'V', 'E'))
	{
		mmioClose(handle, 0);
		return S_FALSE;
	}

	/////////////////////////////////////////////
	//查找 fmt 块
	////////////////////////////////////////////
	mmckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (0 != mmioDescend(handle, &mmckIn, &mmckriff, MMIO_FINDCHUNK))
	{
		mmioClose(handle, 0);
		return S_FALSE;
	}

	////////////////////////////////////////////////////
	//fmt块的格式与PCMWAVEFORMAT 的格式定义相同
	//所以读入临时变量，最后写入 wmtf中
	////////////////////////////////////////////////////
	if (mmioRead(handle, (HPSTR)& pwfm, sizeof(PCMWAVEFORMAT)) != sizeof(PCMWAVEFORMAT))
	{
		mmioClose(handle, 0);
		return S_FALSE;
	}
	////////////////////////////////////
	//检测是不是 pc的wave标准格式
	//
	//////////////////////////////
	if (pwfm.wf.wFormatTag != WAVE_FORMAT_PCM)
	{
		mmioClose(handle, 0);
		return S_FALSE;
	}

	/////////////////////////////
	//给wmfx赋值
	/////////////////////////
	memcpy(&wfmx, &pwfm, sizeof(pwfm));
	wfmx.cbSize = 0;

	if (0 != mmioAscend(handle, &mmckIn, 0))
	{
		mmioClose(handle, 0);
		return S_FALSE;
	}

	/////////////////////////////
	//查找 data chunk
	/////////////////////////
	mmckIn.ckid = mmioFOURCC('d', 'a', 't', 'a');

	if (0 != mmioDescend(handle, &mmckIn, &mmckriff, MMIO_FINDCHUNK))
	{
		mmioClose(handle, 0);
		return S_FALSE;
	}

	sndBuffer = new UCHAR[mmckIn.cksize];

	/////////////////////////////
	//数据写入sndBuffer
	/////////////////////////
	mmioRead(handle, (HPSTR)sndBuffer, mmckIn.cksize);

	mmioClose(handle, 0);

	/////////////////////////////
	//建立directsound的辅助缓存
	//
	/////////////////////////
	memset((void*)&dsbd, 0, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwBufferBytes = mmckIn.cksize;
	dsbd.dwFlags = (control_flags | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE);
	dsbd.lpwfxFormat = &wfmx;
	for (int i = 0; i < maxConcurrentNumber; ++i) {
		HRESULT hr = lpds->CreateSoundBuffer(&dsbd, lpdbsBuffer_ptr + i, NULL);
		if (FAILED(hr))
		{
			delete[] sndBuffer;
			return S_FALSE;
		}
		VOID* pDSLockedBuffer = NULL;
		DWORD dwDSLockedBufferSize = 0;

		////////////////////
		//lock 住内存，现在他是可操作的，拷贝进去即可
		////////////////
		if (FAILED((*(lpdbsBuffer_ptr + i))->Lock(0, mmckIn.cksize, &pDSLockedBuffer, &dwDSLockedBufferSize, NULL, NULL, 0L)))
			return S_FALSE;
		memcpy(pDSLockedBuffer, sndBuffer, mmckIn.cksize);

		///////////////
		//Unlock 缓冲区内存
		//
		////////////////
		if (FAILED((*(lpdbsBuffer_ptr+i))->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0)))
		{
			delete[] sndBuffer;
			return S_FALSE;
		}
	}
	

	return S_OK;
}