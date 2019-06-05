#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "D2DApp.h"
#include "GameRectangle.h"

class GameApp : public D2DApp
{


public:
	GameApp(HINSTANCE hInstance);
	~GameApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();


private:
	bool InitResource();
	GameRectangle *rect;


};


#endif