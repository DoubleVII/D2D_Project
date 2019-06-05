#pragma once
#include "GameRectangle.h"
class StrockRectangle :
	public GameRectangle
{
public:
	StrockRectangle(ComPtr <ID2D1Brush> brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT angle);
	virtual ~StrockRectangle();

	void draw(ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget);
};

