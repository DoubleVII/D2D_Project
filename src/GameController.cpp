#include "GameController.h"
#include "../resource.h"


#include "GameRectangle.h"
#include "StrockRectangle.h"
#include "GameCircle.h"
#include "BitmapRectangle.h"
#include "GirdBackground.h"

using namespace DirectX;


GameRectangle* temRect;
StrockRectangle* temRect2;
GameCircle* temCircle;
BitmapRectangle* temRect3;
GirdBackground* background;


template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;
ComPtr<ID2D1Bitmap> temBitmap;
ComPtr<ID2D1SolidColorBrush> m_pLightSlateGrayBrush;
ComPtr<ID2D1SolidColorBrush> m_pCornflowerBlueBrush;

GameController::GameController(HINSTANCE hInstance)
	: GameApp(hInstance)
{
}

GameController::GameController(HINSTANCE hInstance, int windowWidth, int windowHeight)
	: GameApp(hInstance, windowWidth, windowHeight)
{
}

GameController::~GameController()
{
	delete temRect;
	delete temRect2;
	delete temRect3;
	delete temCircle;
	temBitmap.Reset();
	m_pLightSlateGrayBrush.Reset();
	m_pCornflowerBlueBrush.Reset();
}

void GameController::GameInit()
{
	//例子

	LoadResourceBitmap(MAKEINTRESOURCE(IDB_PNG2), L"PNG", 0, 0, temBitmap.GetAddressOf());
	CreateSolidColorBrush(m_pLightSlateGrayBrush.GetAddressOf(), D2D1::ColorF(D2D1::ColorF::LightSlateGray));
	CreateSolidColorBrush(m_pCornflowerBlueBrush.GetAddressOf(), D2D1::ColorF(D2D1::ColorF::CornflowerBlue));

	//LoadBitmapFromFile(L"head.jpg", 0, 0, temBitmap.GetAddressOf());
	background = new GirdBackground(m_pLightSlateGrayBrush.Get());
	temRect = new GameRectangle(m_pLightSlateGrayBrush.Get(), 100.f, 100.f, 50.f, 80.f, 30.f);
	temRect2 = new StrockRectangle(m_pCornflowerBlueBrush.Get(), 400.f, 300.f, 70.f, 30.f, 5.0f);
	temCircle = new GameCircle(m_pCornflowerBlueBrush.Get(), 600.f, 400.f, 40.f);

	temRect3 = new BitmapRectangle(temBitmap.Get(), ((temBitmap)->GetSize()).width, ((temBitmap)->GetSize()).height);
	addGraphic(background);
	addGraphic(temRect3);
	addGraphic(temRect);
	addGraphic(temRect2);
	addGraphic(temCircle);
}

void GameController::UpdateScene(float dt)
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

	//例子
	//键盘按下
	if (keyState.IsKeyDown(Keyboard::W))
		temRect3->setY(temRect3->getY() - 100.f * dt);
	if (keyState.IsKeyDown(Keyboard::S))
		temRect3->setY(temRect3->getY() + 100.f * dt);
	if (keyState.IsKeyDown(Keyboard::A))
		temRect3->setX(temRect3->getX() - 100.f * dt);
	if (keyState.IsKeyDown(Keyboard::D))
		temRect3->setX(temRect3->getX() + 100.f * dt);
}
