#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "D2DApp.h"
#include "Drawable.h"
#include <list>

#include "GameRectangle.h"
#include "StrockRectangle.h"
#include "GameCircle.h"

class GameApp : public D2DApp
{


public:
	GameApp(HINSTANCE hInstance);
	~GameApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();

	void addGraphic(Drawable* g);
	void removeGraphic(Drawable* g);


private:
	bool InitResource();
	std::list<Drawable*> graphics;
	GameRectangle* temRect;
	StrockRectangle* temRect2;
	GameCircle* temCircle;

};


#endif