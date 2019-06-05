#include "StrockRectangle.h"




StrockRectangle::StrockRectangle(ComPtr<ID2D1Brush> brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT angle)
	:GameRectangle(brush, x, y, width, height, angle)
{
	
}

StrockRectangle::~StrockRectangle()
{
}

void StrockRectangle::draw(ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget)
{
}
