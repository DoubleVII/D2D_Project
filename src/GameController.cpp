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
#include <time.h>
#include <stdlib.h>

using namespace DirectX;

const int base_site = 106;
const int Max_Sequence = 100;
const int Maxn = 5;
const int SPEED = 1000;
const int EFFECT_AREA = 80;
const int SCROE_SITE = 600;

typedef struct NODE
{
	BitmapRectangle* shape;
	int value;   //  0:up  1:down  2:left  3:right
}Node;


GirdBackground* background;
GameText* gameText;
GameSound* sound;

std::wstring textStr = L"Use W,A,S,D to catch the block.";

template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;
ComPtr<ID2D1SolidColorBrush> m_pLightSlateGrayBrush;
ComPtr<ID2D1SolidColorBrush> m_pCornflowerBlueBrush;
ComPtr<IDWriteTextFormat> defaultTextFormat;

ComPtr<ID2D1Bitmap> toLeft[Maxn], toRight[Maxn], toUp[Maxn], toDown[Maxn];
ComPtr<ID2D1Bitmap> toLeftsite, toRightsite, toUpsite, toDownsite;
ComPtr<ID2D1Bitmap> roomBitmap, endGameBitmap;

BitmapRectangle* LeftArrow[Maxn];
BitmapRectangle* RightArrow[Maxn];
BitmapRectangle* UpArrow[Maxn];
BitmapRectangle* DownArrow[Maxn];

BitmapRectangle* Leftsite;
BitmapRectangle* Rightsite;
BitmapRectangle* Upsite;
BitmapRectangle* Downsite;

BitmapRectangle* roomRectangle;
BitmapRectangle* endGameRectangle;
bool flag = true;

time_t start, end;
int site = 0;

Node Sequence[Max_Sequence];   // 0：上  1：下  2：左  3：右
int s_site = 0;
int now_site = 0;

int score = 0;
int life = 100;

GameText* scoreText;
GameText* lifeText;
GameText* showScore;
GameText* showLife;

std::wstring scoreStr = L"Your score: ";
std::wstring showScoreStr = std::to_wstring(score);
std::wstring lifeStr = L"Your life: ";
std::wstring showLifeStr = std::to_wstring(life);



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
	m_pLightSlateGrayBrush.Reset();
	m_pCornflowerBlueBrush.Reset();
	defaultTextFormat.Reset();

	for (int i = 0; i < Maxn; i++)
	{
		delete LeftArrow[i];
		delete RightArrow[i];
		delete UpArrow[i];
		delete DownArrow[i];

		toLeft[i].Reset();
		toRight[i].Reset();
		toUp[i].Reset();
		toDown[i].Reset();
	}

	delete Leftsite;
	delete Rightsite;
	delete Upsite;
	delete Downsite;

	toLeftsite.Reset();
	toRightsite.Reset();
	toUpsite.Reset();
	toDownsite.Reset();
}

void GameController::GameInit()
{
	start = time(NULL);
	site = 0;
	s_site = 0;
	now_site = 0;
	score = 0;
	life = 100;
	srand((unsigned)time(NULL));

	LoadResourceBitmap(MAKEINTRESOURCE(IDB_PNG24), L"PNG", 0, 0, toLeftsite.GetAddressOf());
	LoadResourceBitmap(MAKEINTRESOURCE(IDB_PNG23), L"PNG", 0, 0, toRightsite.GetAddressOf());
	LoadResourceBitmap(MAKEINTRESOURCE(IDB_PNG21), L"PNG", 0, 0, toUpsite.GetAddressOf());
	LoadResourceBitmap(MAKEINTRESOURCE(IDB_PNG22), L"PNG", 0, 0, toDownsite.GetAddressOf());
	LoadResourceBitmap(MAKEINTRESOURCE(IDB_PNG25), L"PNG", 0, 0, roomBitmap.GetAddressOf());
	LoadResourceBitmap(MAKEINTRESOURCE(IDB_PNG26), L"PNG", 0, 0, endGameBitmap.GetAddressOf());

	for (int i = 0; i < Maxn; i++)
	{
		LoadResourceBitmap(MAKEINTRESOURCE(i + base_site), L"PNG", 0, 0, toLeft[i].GetAddressOf());
		LoadResourceBitmap(MAKEINTRESOURCE(i + base_site + 5), L"PNG", 0, 0, toRight[i].GetAddressOf());
		LoadResourceBitmap(MAKEINTRESOURCE(i + base_site + 10), L"PNG", 0, 0, toUp[i].GetAddressOf());
		LoadResourceBitmap(MAKEINTRESOURCE(i + base_site + 15), L"PNG", 0, 0, toDown[i].GetAddressOf());
	}

	//例子
	CreateSolidColorBrush(m_pLightSlateGrayBrush.GetAddressOf(), D2D1::ColorF(D2D1::ColorF::LightSlateGray));
	CreateSolidColorBrush(m_pCornflowerBlueBrush.GetAddressOf(), D2D1::ColorF(D2D1::ColorF::CornflowerBlue));
	CreateTextFormat(defaultTextFormat.GetAddressOf(), 30.f, L"Microsoft YaHei");

	//LoadBitmapFromFile(L"resources/head.jpg", 0, 0, temBitmap.GetAddressOf());
	background = new GirdBackground(m_pLightSlateGrayBrush.Get());


	gameText = new GameText(m_pCornflowerBlueBrush.Get(), defaultTextFormat.Get(), textStr.c_str(), textStr.size(), 0, 0, 1200, 100);
	scoreText = new GameText(m_pCornflowerBlueBrush.Get(), defaultTextFormat.Get(), scoreStr.c_str(), scoreStr.size(), 0, 0, 600, 300);
	showScore = new GameText(m_pCornflowerBlueBrush.Get(), defaultTextFormat.Get(), showScoreStr.c_str(), showScoreStr.size(), 0, 0, 1000, 300);
	lifeText = new GameText(m_pCornflowerBlueBrush.Get(), defaultTextFormat.Get(), lifeStr.c_str(), lifeStr.size(), 0, 0, 600, 500);
	showLife = new GameText(m_pCornflowerBlueBrush.Get(), defaultTextFormat.Get(), showLifeStr.c_str(), showLifeStr.size(), 0, 0, 1000, 500);

	Leftsite = new BitmapRectangle(toLeftsite.Get(), ((toLeftsite)->GetSize()).width, ((toLeftsite)->GetSize()).height);
	Rightsite = new BitmapRectangle(toRightsite.Get(), ((toRightsite)->GetSize()).width, ((toRightsite)->GetSize()).height);
	Upsite = new BitmapRectangle(toUpsite.Get(), ((toUpsite)->GetSize()).width, ((toUpsite)->GetSize()).height);
	Downsite = new BitmapRectangle(toDownsite.Get(), ((toDownsite)->GetSize()).width, ((toDownsite)->GetSize()).height);

	roomRectangle = new BitmapRectangle(roomBitmap.Get(), 1500, 800);
	endGameRectangle = new BitmapRectangle(endGameBitmap.Get(), ((endGameBitmap)->GetSize()).width, ((endGameBitmap)->GetSize()).height);

	Leftsite->setX(300);
	Leftsite->setY(SCROE_SITE);

	Rightsite->setX(700);
	Rightsite->setY(SCROE_SITE);

	Upsite->setX(500);
	Upsite->setY(SCROE_SITE);

	Downsite->setX(900);
	Downsite->setY(SCROE_SITE);

	for (int i = 0; i < Maxn; i++)
	{
		LeftArrow[i] = new BitmapRectangle(toLeft[i].Get(), ((toLeft[i])->GetSize()).width, ((toLeft[i])->GetSize()).height);
		RightArrow[i] = new BitmapRectangle(toRight[i].Get(), ((toRight[i])->GetSize()).width, ((toRight[i])->GetSize()).height);
		UpArrow[i] = new BitmapRectangle(toUp[i].Get(), ((toUp[i])->GetSize()).width, ((toUp[i])->GetSize()).height);
		DownArrow[i] = new BitmapRectangle(toDown[i].Get(), ((toDown[i])->GetSize()).width, ((toDown[i])->GetSize()).height);
	}


	addGraphic(background);
	addGraphic(roomRectangle);
	addGraphic(gameText);
	addGraphic(scoreText);
	addGraphic(lifeText);
	addGraphic(showScore);
	addGraphic(showLife);

	addGraphic(Leftsite);
	addGraphic(Rightsite);
	addGraphic(Upsite);
	addGraphic(Downsite);

	soundAdapter.createSound((LPWSTR)L"resources/M11-07-27.wav", &sound, 10);
	sound->play();
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

	if (flag == true) {
		showScoreStr = std::to_wstring(score);
		showScore->setText(showScoreStr.c_str(), showScoreStr.size());

		showLifeStr = std::to_wstring(life);
		showLife->setText(showLifeStr.c_str(), showLifeStr.size());

		int x = 1;
		if (m_KeyboardTracker.lastState.IsKeyUp(Keyboard::W) && keyState.IsKeyDown(Keyboard::W)) {

			x++;
		}
		if (x == 10) {
			x++;
		}

		for (int i = 0; i < Maxn; i++)
		{
			LeftArrow[i]->setY(LeftArrow[i]->getY() + SPEED * dt);
			RightArrow[i]->setY(RightArrow[i]->getY() + SPEED * dt);
			UpArrow[i]->setY(UpArrow[i]->getY() + SPEED * dt);
			DownArrow[i]->setY(DownArrow[i]->getY() + SPEED * dt);
		}

		end = time(NULL);

		while (end - start == 2)
		{
			start = end;
			int num = rand() % 4;
			//int num = 2;

			switch (num)
			{
			case 0:LeftArrow[site]->setX(325);
				LeftArrow[site]->setY(0);
				Sequence[s_site].shape = LeftArrow[site];
				Sequence[s_site].value = 2;
				addGraphic(LeftArrow[site]);
				break;
			case 1:RightArrow[site]->setX(725);
				RightArrow[site]->setY(0);
				Sequence[s_site].shape = RightArrow[site];
				Sequence[s_site].value = 3;
				addGraphic(RightArrow[site]);
				break;
			case 2:UpArrow[site]->setX(525);
				UpArrow[site]->setY(0);
				Sequence[s_site].shape = UpArrow[site];
				Sequence[s_site].value = 0;
				addGraphic(UpArrow[site]);
				break;
			case 3:DownArrow[site]->setX(925);
				DownArrow[site]->setY(0);
				Sequence[s_site].shape = DownArrow[site];
				Sequence[s_site].value = 1;
				addGraphic(DownArrow[site]);
				break;
			default:
				break;
			}

			site = (site + 1) % Maxn;
			s_site = (s_site + 1) % Max_Sequence;
		}


		//键盘输入
		if ((s_site - now_site) % Max_Sequence >= 1)
		{
			if (Sequence[now_site].value == 0)
			{
				if (Sequence[now_site].shape->getY() - Upsite->getY() < EFFECT_AREA && Sequence[now_site].shape->getY() - Upsite->getY() > -EFFECT_AREA)
				{
					if (keyState.IsKeyDown(Keyboard::W))
					{
						removeGraphic(Sequence[now_site].shape);
						now_site = (now_site + 1) % Max_Sequence;

						score++;
					}
				}
				else if (Sequence[now_site].shape->getY() - Upsite->getY() >= EFFECT_AREA)
				{
					removeGraphic(Sequence[now_site].shape);
					now_site = (now_site + 1) % Max_Sequence;

					life -= 10;
				}
			}
			if (Sequence[now_site].value == 1)
			{
				if (Sequence[now_site].shape->getY() - Downsite->getY() < EFFECT_AREA && Sequence[now_site].shape->getY() - Downsite->getY() > -EFFECT_AREA)
				{
					if (keyState.IsKeyDown(Keyboard::S))
					{
						removeGraphic(Sequence[now_site].shape);
						now_site = (now_site + 1) % Max_Sequence;

						score++;
					}
				}
				else if (Sequence[now_site].shape->getY() - Downsite->getY() >= EFFECT_AREA)
				{
					removeGraphic(Sequence[now_site].shape);
					now_site = (now_site + 1) % Max_Sequence;

					life -= 10;
				}
			}
			if (Sequence[now_site].value == 2)
			{
				if (Sequence[now_site].shape->getY() - Leftsite->getY() < EFFECT_AREA && Sequence[now_site].shape->getY() - Leftsite->getY() > -EFFECT_AREA)
				{
					if (keyState.IsKeyDown(Keyboard::A))
					{
						removeGraphic(Sequence[now_site].shape);
						now_site = (now_site + 1) % Max_Sequence;

						score++;
					}
				}
				else if (Sequence[now_site].shape->getY() - Leftsite->getY() >= EFFECT_AREA)
				{
					removeGraphic(Sequence[now_site].shape);
					now_site = (now_site + 1) % Max_Sequence;

					life -= 10;
				}
			}
			if (Sequence[now_site].value == 3)
			{
				if (Sequence[now_site].shape->getY() - Rightsite->getY() < EFFECT_AREA && Sequence[now_site].shape->getY() - Rightsite->getY() > -EFFECT_AREA)
				{
					if (keyState.IsKeyDown(Keyboard::D))
					{
						removeGraphic(Sequence[now_site].shape);
						now_site = (now_site + 1) % Max_Sequence;

						score++;
					}
				}
				else if (Sequence[now_site].shape->getY() - Rightsite->getY() >= EFFECT_AREA)
				{
					removeGraphic(Sequence[now_site].shape);
					now_site = (now_site + 1) % Max_Sequence;

					life -= 10;
				}
			}
		}


		// 最后更新键盘状态
		m_KeyboardTracker.Update(keyState);
		if (life < 0)
		{
			flag = false;
		}
	}
	else {
		endGameRectangle->setX(350);
		endGameRectangle->setY(300);
		addGraphic(endGameRectangle);
		sound->stop();
		if (keyState.IsKeyDown(Keyboard::Q)) {
			exit(0);
		}
		else if (keyState.IsKeyDown(Keyboard::R)) {
			score = 0;
			life = 100;
			removeGraphic(endGameRectangle);
			flag = true;
			sound->play();
		}
	}
}
