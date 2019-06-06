#include "RoundedRectangle.h"

RoundedRectangle::RoundedRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT radius, FLOAT angle) :
	GameRectangle(brush, x, y, width, height, angle), radius(radius)
{
}

RoundedRectangle::RoundedRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT radius) :
	GameRectangle(brush, x, y, width, height), radius(radius)
{
}

RoundedRectangle::RoundedRectangle(ID2D1Brush* brush, FLOAT width, FLOAT height, FLOAT radius) :
	GameRectangle(brush, width, height), radius(radius)
{
}

RoundedRectangle::~RoundedRectangle()
{
}

void RoundedRectangle::drawStyle(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	assert(brush);
	m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(
		D2D1::RectF(
		x - width / 2,
		y - height / 2,
		x + width / 2,
		y + height / 2),
		radius,
		radius),
		brush);
}
