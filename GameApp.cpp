#include "GameApp.h"


using namespace DirectX;


GameApp::GameApp(HINSTANCE hInstance)
	: D2DApp(hInstance),
	graphics(),
	temRect(nullptr)
{
}

GameApp::~GameApp()
{
	delete temRect;
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

	//例子
	temRect = new GameRectangle(m_pLightSlateGrayBrush, 100.f, 100.f, 50.f, 80.f, 30.f);
	temRect2 = new StrockRectangle(m_pCornflowerBlueBrush, 400.f, 300.f, 70.f, 30.f, 5.0f);
	temCircle = new GameCircle(m_pCornflowerBlueBrush, 600.f, 400.f, 40.f);
	addGraphic(temRect);
	addGraphic(temRect2);
	addGraphic(temCircle);
	return true;
}

void GameApp::OnResize()
{
	D2DApp::OnResize();
}

void GameApp::UpdateScene(float dt)
{
	// 获取鼠标状态
	Mouse::State mouseState = m_pMouse->GetState();
	Mouse::State lastMouseState = m_MouseTracker.GetLastState();
	// 获取键盘状态
	Keyboard::State keyState = m_pKeyboard->GetState();
	Keyboard::State lastKeyState = m_KeyboardTracker.GetLastState();

	// 更新鼠标按钮状态跟踪器
	m_MouseTracker.Update(mouseState);
	m_KeyboardTracker.Update(keyState);


	//例子
	//鼠标拖动
	if (mouseState.leftButton == true && m_MouseTracker.leftButton == m_MouseTracker.HELD) {

	}

	
	GameRectangle* rect = dynamic_cast<GameRectangle*>(graphics.front());

	//例子
	//键盘按下
	if (keyState.IsKeyDown(Keyboard::W))
		rect->setY(rect->getY() - 100.f * dt);
	if (keyState.IsKeyDown(Keyboard::S))
		rect->setY(rect->getY() + 100.f * dt);
	if (keyState.IsKeyDown(Keyboard::A))
		rect->setX(rect->getX() - 100.f * dt);
	if (keyState.IsKeyDown(Keyboard::D))
		rect->setX(rect->getX() + 100.f * dt);
		
}

void GameApp::DrawScene()
{
	//assert(m_pd3dImmediateContext);
	//assert(m_pSwapChain);

	HRESULT hr = S_OK;
	assert(m_pRenderTarget);
	m_pRenderTarget->BeginDraw();


	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

	// Draw a grid background.
	int width = static_cast<int>(rtSize.width);
	int height = static_cast<int>(rtSize.height);

	for (int x = 0; x < width; x += 10)
	{
		m_pRenderTarget->DrawLine(
			D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
			D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
			m_pLightSlateGrayBrush.Get(),
			0.5f
		);
	}

	for (int y = 0; y < height; y += 10)
	{
		m_pRenderTarget->DrawLine(
			D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
			D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
			m_pLightSlateGrayBrush.Get(),
			0.5f
		);
	}

	auto iter = graphics.begin();
	while (iter != graphics.end())
	{
		(*iter)->draw(m_pRenderTarget);
		++iter;
	}
	
	

	// Draw two rectangles.
	//D2D1_RECT_F rectangle1 = D2D1::RectF(
	//	rtSize.width / 2 - 50.0f + x,
	//	rtSize.height / 2 - 50.0f + y,
	//	rtSize.width / 2 + 50.0f + x,
	//	rtSize.height / 2 + 50.0f + y
	//);

	//D2D1_RECT_F rectangle2 = D2D1::RectF(
	//	rtSize.width / 2 - 100.0f,
	//	rtSize.height / 2 - 100.0f,
	//	rtSize.width / 2 + 100.0f,
	//	rtSize.height / 2 + 100.0f
	//);

	//// Draw a filled rectangle.
	//m_pRenderTarget->FillRectangle(&rectangle1, m_pLightSlateGrayBrush.Get());

	//// Draw the outline of a rectangle.
	//m_pRenderTarget->DrawRectangle(&rectangle2, m_pCornflowerBlueBrush.Get());

	hr = m_pRenderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
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
