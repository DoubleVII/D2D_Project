#include "GameController.h"
#include "../resource.h"
#include <string>

#include "GameRectangle.h"
#include "StrokeRectangle.h"
#include "GameCircle.h"
#include "BitmapRectangle.h"
#include "GirdBackground.h"
#include "RoundedRectangle.h"
#include "StrokeRoundedRectangle.h"
#include "GameLine.h"
#include "GameText.h"

using namespace DirectX;


GameRectangle* temRect;
StrokeRectangle* temRect2;
GameCircle* temCircle;
BitmapRectangle* temRect3;
GirdBackground* background;
RoundedRectangle* temRect4;
StrokeRoundedRectangle* temRect5;
GameLine* line;
GameText* gameText;
GameSound* sound;

std::wstring textStr = L"Use W,A,S,D to move.";

template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;
ComPtr<ID2D1Bitmap> temBitmap;
ComPtr<ID2D1SolidColorBrush> m_pLightSlateGrayBrush;
ComPtr<ID2D1SolidColorBrush> m_pCornflowerBlueBrush;
ComPtr<IDWriteTextFormat> defaultTextFormat;

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
	delete temRect4;
	delete temRect5;
	delete line;
	temBitmap.Reset();
	m_pLightSlateGrayBrush.Reset();
	m_pCornflowerBlueBrush.Reset();
	defaultTextFormat.Reset();
}

void GameController::GameInit()
{
	//例子
	LoadResourceBitmap(MAKEINTRESOURCE(IDB_PNG2), L"PNG", 0, 0, temBitmap.GetAddressOf());
	CreateSolidColorBrush(m_pLightSlateGrayBrush.GetAddressOf(), D2D1::ColorF(D2D1::ColorF::LightSlateGray));
	CreateSolidColorBrush(m_pCornflowerBlueBrush.GetAddressOf(), D2D1::ColorF(D2D1::ColorF::CornflowerBlue));
	CreateTextFormat(defaultTextFormat.GetAddressOf(), 30.f, L"Microsoft YaHei");

	//LoadBitmapFromFile(L"resources/head.jpg", 0, 0, temBitmap.GetAddressOf());
	background = new GirdBackground(m_pLightSlateGrayBrush.Get());
	temRect = new GameRectangle(m_pLightSlateGrayBrush.Get(), 100.f, 100.f, 50.f, 80.f, 30.f);
	temRect2 = new StrokeRectangle(m_pCornflowerBlueBrush.Get(), 400.f, 300.f, 70.f, 30.f, 5.0f);
	temCircle = new GameCircle(m_pCornflowerBlueBrush.Get(), 600.f, 400.f, 40.f);
	temRect4 = new RoundedRectangle(m_pLightSlateGrayBrush.Get(), 300.f, 500.f, 120.f, 50.f, 10.f);
	temRect5 = new StrokeRoundedRectangle(m_pLightSlateGrayBrush.Get(), 500.f, 500.f, 120.f, 50.f, 3.f, 10.f);
	line = new GameLine(m_pCornflowerBlueBrush.Get(), 300.f, 300.f, 600.f, 900.f, 3.f);

	


	gameText = new GameText(m_pCornflowerBlueBrush.Get(), defaultTextFormat.Get(), textStr.c_str(), textStr.size(), 0, 0, 1200, 100);

	temRect3 = new BitmapRectangle(temBitmap.Get(), ((temBitmap)->GetSize()).width, ((temBitmap)->GetSize()).height);
	
	addGraphic(background);
	addGraphic(gameText);
	addGraphic(temRect3);
	addGraphic(temRect);
	addGraphic(temRect2);
	addGraphic(temRect4);
	addGraphic(temRect5);
	addGraphic(temCircle);
	//addGraphic(line);
	

	soundAdapter.createSound((LPWSTR)L"resources/M11-07-27.wav", &sound, 10);
	sound->play();
	sound->stop();
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
	
	int x = 1;
	if(m_KeyboardTracker.lastState.IsKeyUp(Keyboard::W) && keyState.IsKeyDown(Keyboard::W)) {
		
		x++;
	}
	if (x == 10) {
		x++;
	}
	// 例子
	// 鼠标拖动
	if (mouseState.leftButton == true && m_MouseTracker.leftButton == m_MouseTracker.HELD) {
		
	}

	if (mouseState.x > temRect3->getX() && mouseState.x < temRect3->getX() + temRect3->getWidth() && mouseState.y > temRect3->getY() && mouseState.y < temRect3->getY() + temRect3->getHeight()) {
		temRect3->setOpacity(0.5f);
	}
	else {
		temRect3->setOpacity(1.0f);
	}

	// 例子
	// 键盘按下
	if (keyState.IsKeyDown(Keyboard::W))
		temRect3->setY(temRect3->getY() - 100.f * dt);
	if (keyState.IsKeyDown(Keyboard::S))
		temRect3->setY(temRect3->getY() + 100.f * dt);
	if (keyState.IsKeyDown(Keyboard::A))
		temRect3->setX(temRect3->getX() - 100.f * dt);
	if (keyState.IsKeyDown(Keyboard::D))
		temRect3->setX(temRect3->getX() + 100.f * dt);


	// 最后更新键盘状态
	m_KeyboardTracker.Update(keyState);
}
