// Windows Header Files:
#include <windows.h>

// C RunTime Header Files:
#include <assert.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#include <wrl/client.h>
#include <string>

#include "GameTimer.h"

#include "Mouse.h"
#include "Keyboard.h"

// �������Ҫ���õĿ�
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "Windowscodecs.lib")

#pragma once


template<class Interface>
inline void SafeRelease(
	Interface** ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}


#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif



#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

class D2DApp
{
public:
	D2DApp(HINSTANCE hInstance);
	virtual ~D2DApp();

	// Process and dispatch messages
	//@deprecated void RunMessageLoop();

	HINSTANCE AppInst()const;       // ��ȡӦ��ʵ���ľ��
	HWND      MainWnd()const;       // ��ȡ�����ھ��
	float     AspectRatio()const;   // ��ȡ��Ļ��߱�

	int Run();                      // ���г��򣬽�����Ϸ��ѭ��

	// ��ܷ������ͻ���������Ҫ������Щ������ʵ���ض���Ӧ������
	virtual bool Init();                      // �ø��෽����Ҫ��ʼ�����ں�Direct3D����
	virtual void OnResize();                  // �ø��෽����Ҫ�ڴ��ڴ�С�䶯��ʱ�����
	virtual void UpdateScene(float dt) = 0;   // ������Ҫʵ�ָ÷��������ÿһ֡�ĸ���
	virtual void DrawScene() = 0;             // ������Ҫʵ�ָ÷��������ÿһ֡�Ļ���
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


protected:
	bool InitMainWindow();       // ���ڳ�ʼ��
	bool InitDirect2D();         // Direct3D��ʼ��

	void CalculateFrameStats();  // ����ÿ��֡�����ڴ�����ʾ

protected:

	HINSTANCE m_hAppInst;        // Ӧ��ʵ�����
	HWND      m_hMainWnd;        // �����ھ��
	bool      m_AppPaused;       // Ӧ���Ƿ���ͣ
	bool      m_Minimized;       // Ӧ���Ƿ���С��
	bool      m_Maximized;       // Ӧ���Ƿ����
	bool      m_Resizing;        // ���ڴ�С�Ƿ�仯


	GameTimer m_Timer;           // ��ʱ��

protected:
	// Initialize device-independent resources.
	HRESULT CreateDeviceIndependentResources();

	// Initialize device-dependent resources.
	HRESULT CreateDeviceResources();

	// Release device-dependent resource.
	void DiscardDeviceResources();

	HRESULT LoadResourceBitmap(
		PCWSTR resourceName,
		PCWSTR resourceType,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap);

	HRESULT LoadBitmapFromFile(
		LPCWSTR uri,
		UINT width,
		UINT height,
		ID2D1Bitmap** ppBitmap);

protected:
	template <class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
	ComPtr<ID2D1Factory> m_pDirect2dFactory;
	ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget;
	ComPtr<ID2D1SolidColorBrush> m_pLightSlateGrayBrush;
	ComPtr<ID2D1SolidColorBrush> m_pCornflowerBlueBrush;
	ComPtr<IWICImagingFactory> m_pImageFactory;

	// ��������
	std::unique_ptr<DirectX::Mouse> m_pMouse;						// ���
	DirectX::Mouse::ButtonStateTracker m_MouseTracker;				// ���״̬׷����
	std::unique_ptr<DirectX::Keyboard> m_pKeyboard;					// ����
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;		// ����״̬׷����

	float x = 0, y = 0;

	// ������Ӧ���ڹ��캯�����ú���Щ�Զ���ĳ�ʼ����
	std::wstring m_MainWndCaption;                        // �����ڱ���
	int m_ClientWidth;                                    // �ӿڿ��
	int m_ClientHeight;                                   // �ӿڸ߶�

};