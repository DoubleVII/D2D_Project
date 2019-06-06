#pragma once
#include "GameRectangle.h"
class StrokeRectangle :
	public GameRectangle
{
public:
	StrokeRectangle(ID2D1Brush* brush, FLOAT width, FLOAT height);
	StrokeRectangle(ID2D1Brush* brush, FLOAT width, FLOAT height, FLOAT strokeWidth);
	StrokeRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT strokeWidth);
	StrokeRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height);
	StrokeRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT angle, FLOAT strokeWidth);
	virtual ~StrokeRectangle();

	void drawStyle(ID2D1HwndRenderTarget* m_pRenderTarget);

	void setSrokeWidth(FLOAT strokeWidth) {
		this->strokeWidth = strokeWidth;
	}
	
	FLOAT getSrokeWidth() {
		return strokeWidth;
	}

protected:
	FLOAT strokeWidth;
};

