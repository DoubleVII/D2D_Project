#pragma once
#include "StrokeRectangle.h"
class StrokeRoundedRectangle :
	public StrokeRectangle
{
public:
	StrokeRoundedRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT angle, FLOAT strokeWidth, FLOAT radius);
	StrokeRoundedRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT strokeWidth, FLOAT radius);
	StrokeRoundedRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT radius);
	StrokeRoundedRectangle(ID2D1Brush* brush, FLOAT width, FLOAT height, FLOAT strokeWidth, FLOAT radius);
	StrokeRoundedRectangle(ID2D1Brush* brush, FLOAT width, FLOAT height, FLOAT radius);
	virtual ~StrokeRoundedRectangle();

	void drawStyle(ID2D1HwndRenderTarget* m_pRenderTarget);

private:
	FLOAT radius;
};

