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

// 添加所有要引用的库
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

	HINSTANCE AppInst()const;       // 获取应用实例的句柄
	HWND      MainWnd()const;       // 获取主窗口句柄
	float     AspectRatio()const;   // 获取屏幕宽高比

	int Run();                      // 运行程序，进行游戏主循环

	// 框架方法。客户派生类需要重载这些方法以实现特定的应用需求
	virtual bool Init();                      // 该父类方法需要初始化窗口和Direct3D部分
	virtual void OnResize();                  // 该父类方法需要在窗口大小变动的时候调用
	virtual void UpdateScene(float dt) = 0;   // 子类需要实现该方法，完成每一帧的更新
	virtual void DrawScene() = 0;             // 子类需要实现该方法，完成每一帧的绘制
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


protected:
	bool InitMainWindow();       // 窗口初始化
	bool InitDirect2D();         // Direct3D初始化

	void CalculateFrameStats();  // 计算每秒帧数并在窗口显示

protected:

	HINSTANCE m_hAppInst;        // 应用实例句柄
	HWND      m_hMainWnd;        // 主窗口句柄
	bool      m_AppPaused;       // 应用是否暂停
	bool      m_Minimized;       // 应用是否最小化
	bool      m_Maximized;       // 应用是否最大化
	bool      m_Resizing;        // 窗口大小是否变化


	GameTimer m_Timer;           // 计时器

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

	// 键鼠输入
	std::unique_ptr<DirectX::Mouse> m_pMouse;						// 鼠标
	DirectX::Mouse::ButtonStateTracker m_MouseTracker;				// 鼠标状态追踪器
	std::unique_ptr<DirectX::Keyboard> m_pKeyboard;					// 键盘
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;		// 键盘状态追踪器

	float x = 0, y = 0;

	// 派生类应该在构造函数设置好这些自定义的初始参数
	std::wstring m_MainWndCaption;                        // 主窗口标题
	int m_ClientWidth;                                    // 视口宽度
	int m_ClientHeight;                                   // 视口高度

};