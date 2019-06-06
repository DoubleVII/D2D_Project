#include "GameApp.h"


GameApp::GameApp(HINSTANCE hInstance)
	: D2DApp(hInstance),
	graphics()
{
}

GameApp::GameApp(HINSTANCE hInstance, int windowWidth, int windowHeight)
	: D2DApp(hInstance, windowWidth, windowHeight),
	graphics()
{}

GameApp::~GameApp()
{
	
}

bool GameApp::Init()
{
	if (!D2DApp::Init())
		return false;

	if (!InitResource())
		return false;

	// 初始化鼠标，键盘不需要
	m_pMouse->SetWindow(m_hMainWnd);
	m_pMouse->SetMode(DirectX::Mouse::MODE_ABSOLUTE);


	GameInit();
	
	return true;
}

void GameApp::OnResize()
{
	D2DApp::OnResize();
}


void GameApp::DrawScene()
{
	//assert(m_pd3dImmediateContext);
	//assert(m_pSwapChain);

	HRESULT hr = S_OK;
	assert(m_pRenderTarget);
	m_pRenderTarget->BeginDraw();


	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	auto iter = graphics.begin();
	while (iter != graphics.end())
	{
		(*iter)->draw(m_pRenderTarget.Get());
		++iter;
	}
	

	hr = m_pRenderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		m_pRenderTarget.Reset();
		m_pImageFactory.Reset();
		CreateDeviceResources();
	}
}

void GameApp::addGraphic(Drawable* g)
{
	graphics.push_back(g);
}

void GameApp::removeGraphic(Drawable* g)
{
	graphics.remove(g);
}


bool GameApp::InitResource()
{
	return true;
}
