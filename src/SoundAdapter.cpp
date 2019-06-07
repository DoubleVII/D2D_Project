#include "SoundAdapter.h"



SoundAdapter::SoundAdapter()
{
}


SoundAdapter::~SoundAdapter()
{
}



#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
using namespace std;


#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")
#define WINCLASSNAME "winclass1"

#ifndef DSBCAPS_CTRLDEFAULT
#define DSBCAPS_CTRLDEFAULT (DSBCAPS_CTRLFREQUENCY  | DSBCAPS_CTRLPAN  | DSBCAPS_CTRLVOLUME)
#endif


//---------------------------------------
LPDIRECTSOUND8 g_pDS = NULL;
LPDIRECTSOUNDBUFFER g_pDsbuffer[3] = NULL;
//CWaveFile* g_pWaveFile;//
WAVEFORMATEX g_wfxInput; //输入的音频格式

LPDIRECTSOUNDBUFFER LoadWaveFile(LPSTR lpzFileName)

{

	DSBUFFERDESC dsbdesc;

	HRESULT hr;

	BYTE* pBuffer;

	DWORD dwSizeRead;

	LPDIRECTSOUNDBUFFER lpdsbStatic = NULL;

	if (FAILED(hr = g_pWaveFile->Open(lpzFileName, &g_wfxInput, WAVEFILE_WRITE)))

		return NULL;

	DWORD dwSize = g_pWaveFile->GetSize();

	pBuffer = new BYTE[dwSize];

	g_pWaveFile->Read(pBuffer, dwSize, &dwSizeRead);

	if (dwSizeRead > 0)

	{

		memset((void*)dsbdesc, 0, sizeof(DSBUFFERDESC));

		dsbdesc.dwSize = sizeof(DSBUFFERDESC);

		dsbdesc.dwFlags = DSBCAPS_STATIC;

		dsbdesc.dwBufferBytes = dwSizeRead;

		dsbdesc.lpwfxFormat = g_wfxInput;

		if (FAILED(g_pDS->CreateSoundBuffer(&dsbdesc, &lpdsbStatic, NULL)))

		{

			g_pWaveFile->Close();

			delete pBuffer;

			return NULL;

		}

		LPVOID lpvWrite;

		DWORD dwLength;

		if (DS_OK == lpdsbStatic->Lock(

			0, // Offset at which to start lock.

			0, // Size of lock; ignored because of flag.

			&lpvWrite, // Gets address of first part of lock.

			&dwLength, // Gets size of first part of lock.

			NULL, // Address of wraparound not needed.

			NULL, // Size of wraparound not needed.

			DSBLOCK_ENTIREBUFFER)) // Flag.

		{

			memcpy(lpvWrite, pBuffer, dwLength);

			lpdsbStatic->Unlock(

				lpvWrite, // Address oflock start.

				dwLength, // Size of lock.

				NULL, // No wraparoundportion.

				0); // No wraparound size.

		}

	}

	delete pBuffer;

	return lpdsbStatic;

}

////////////////////////////////
LPDIRECTSOUND    lpds = NULL;


HWND            main_window_handle = NULL;
//////////////////////////////////
LRESULT    CALLBACK    WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
int GameInit(void* params = NULL, int num = 0);
int GameMain(void* params = NULL, int num = 0);
int GameShutdown(void* params = NULL, int num = 0);
HRESULT DSound_Load_Wav(LPWSTR filename, int control_flags = DSBCAPS_CTRLDEFAULT);

int GameInit(void* params, int num)
{
	if (DirectSoundCreate(NULL, &lpds, NULL) != DS_OK)
		return 0;

	if (lpds->SetCooperativeLevel(main_window_handle, DSSCL_PRIORITY) != DS_OK)
		return 0;
	DSound_Load_Wav((LPWSTR)"Windows XP Startup.wav");

	lpdbsBuffer->Play(0, 0, 1);
	return 1;
}
//-----------------------------------------------------------
//名称：DSound_Load_Wav
//功能：利用微软提供的mmio库，解析wav文件，将数据读入内存，然后拷贝到
//DirectSound建立的 辅助缓冲区 从而实现文件的播放（GameInit()）
//----------------------------------------------------------


HRESULT DSound_Load_Wav(LPWSTR filename, int control_flags, LPDIRECTSOUNDBUFFER* lpdbsBuffer_ptr)
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
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwBufferBytes = mmckIn.cksize;
	dsbd.dwFlags = (control_flags | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE);
	dsbd.lpwfxFormat = &wfmx;

	if (FAILED(lpds->CreateSoundBuffer(&dsbd, lpdbsBuffer_ptr, NULL)))
	{
		delete[] sndBuffer;
		return S_FALSE;
	}
	VOID* pDSLockedBuffer = NULL;
	DWORD    dwDSLockedBufferSize = 0;

	////////////////////
	//lock 住内存，现在他是可操作的，拷贝进去即可
	////////////////
	if (FAILED((*lpdbsBuffer_ptr)->Lock(0, mmckIn.cksize, &pDSLockedBuffer, &dwDSLockedBufferSize, NULL, NULL, 0L)))
		return S_FALSE;
	memcpy(pDSLockedBuffer, sndBuffer, mmckIn.cksize);

	///////////////
	//Unlock 缓冲区内存
	//
	////////////////
	if (FAILED((*lpdbsBuffer_ptr)->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0)))
	{
		delete[] sndBuffer;
		return S_FALSE;
	}

	return S_OK;
}
int GameMain(void* params, int num)
{
	return 1;
}
INT WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR lCmdline, int nCmdshow)
{
	MSG    msg;
	HWND hwnd;
	WNDCLASSEX wndclass;

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 255, 255));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hinst;
	wndclass.lpfnWndProc = WinProc;
	wndclass.lpszClassName = WINCLASSNAME;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndclass);

	if (!(hwnd = CreateWindowEx(NULL, WINCLASSNAME, "DSOUND DEMO",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0,
		640, 480,
		NULL,
		NULL,
		hinst,
		NULL)))
		return 0;

	main_window_handle = hwnd;
	GameInit();
	while (TRUE)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			GameMain();
		}
	}
	return (int)(msg.wParam);
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT        ps;
	HDC                hdc;

	switch (msg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return (DefWindowProc(hwnd, msg, wparam, lparam));
}