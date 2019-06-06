#pragma once
#include "GameRectangle.h"
class StrockRectangle :
	public GameRectangle
{
public:
	StrockRectangle(ID2D1Brush* brush, FLOAT width, FLOAT height);
	StrockRectangle(ID2D1Brush* brush, FLOAT width, FLOAT height, FLOAT strokeWidth);
	StrockRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT strokeWidth);
	StrockRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height);
	StrockRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT angle, FLOAT strokeWidth);
	virtual ~StrockRectangle();

	void drawStyle(ID2D1HwndRenderTarget* m_pRenderTarget);

	void setSrokeWidth(FLOAT strokeWidth) {
		this->strokeWidth = strokeWidth;
	}
	
	FLOAT getSrokeWidth() {
		return strokeWidth;
	}

private:
	FLOAT strokeWidth;
};
