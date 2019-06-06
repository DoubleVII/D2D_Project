#pragma once
#include "Drawable.h"
class GameLine :
	public Drawable
{
public:
	GameLine(ID2D1Brush* brush, FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT stroke);
	GameLine(ID2D1Brush* brush, FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2);
	virtual ~GameLine();

	void draw(ID2D1HwndRenderTarget* m_pRenderTarget);

protected:
	FLOAT x1, y1, x2, y2;
	FLOAT strock;
	ID2D1Brush* brush;
};

