#include "StrockRectangle.h"




StrockRectangle::StrockRectangle(ComPtr<ID2D1Brush> brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height)
	:GameRectangle(brush, x, y, width, height), strokeWidth(1.0f)
{
}

StrockRectangle::StrockRectangle(ComPtr<ID2D1Brush> brush, FLOAT width, FLOAT height)
	: GameRectangle(brush, width, height), strokeWidth(1.0f)
{
}

StrockRectangle::StrockRectangle(ComPtr<ID2D1Brush> brush, FLOAT width, FLOAT height, FLOAT strokeWidth)
	: GameRectangle(brush, width, height), strokeWidth(strokeWidth)
{
}

StrockRectangle::StrockRectangle(ComPtr<ID2D1Brush> brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT strokeWidth)
	:GameRectangle(brush, x, y, width, height, angle),strokeWidth(strokeWidth)
{
}

StrockRectangle::StrockRectangle(ComPtr<ID2D1Brush> brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT angle, FLOAT strokeWidth)
	: GameRectangle(brush, x, y, width, height, angle), strokeWidth(strokeWidth)
{
}

StrockRectangle::~StrockRectangle()
{
}

void StrockRectangle::drawStyle(ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget)
{
	m_pRenderTarget->DrawRectangle(D2D1::RectF(
		x - width / 2,
		y - height / 2,
		x + width / 2,
		y + height / 2),
		brush.Get(), strokeWidth);
}
