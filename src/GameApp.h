#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "D2DApp.h"
#include "Drawable.h"
#include <list>

class GameApp : public D2DApp
{


public:
	GameApp(HINSTANCE hInstance);
	GameApp(HINSTANCE hInstance, int windowWidth, int windowHeight);
	~GameApp();

	bool Init();
	void OnResize();
	//void UpdateScene(float dt);
	void DrawScene();

	void addGraphic(Drawable* g);
	void removeGraphic(Drawable* g);


private:
	bool InitResource();
	std::list<Drawable*> graphics;

protected:
	virtual void GameInit() = 0;
};




#endif