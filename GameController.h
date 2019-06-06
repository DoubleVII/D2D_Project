#pragma once
#include "GameApp.h"



class GameController :
	public GameApp
{
public:
	GameController(HINSTANCE hInstance);
	GameController(HINSTANCE hInstance, int windowWidth, int windowHeight);
	virtual ~GameController();

private:
	void GameInit();
	void UpdateScene(float dt);
};

