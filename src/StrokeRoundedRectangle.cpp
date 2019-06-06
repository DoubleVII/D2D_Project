#include "StrokeRoundedRectangle.h"




StrokeRoundedRectangle::StrokeRoundedRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT angle, FLOAT strokeWidth, FLOAT radius) :
	StrokeRectangle(brush, x, y, width, height, angle, strokeWidth), radius(radius)
{
}

StrokeRoundedRectangle::StrokeRoundedRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT strokeWidth, FLOAT radius) :
	StrokeRectangle(brush, x, y, width, height, strokeWidth), radius(radius)
{
}

StrokeRoundedRectangle::StrokeRoundedRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT radius):
	StrokeRectangle(brush, x, y, width, height), radius(radius)
{
}

StrokeRoundedRectangle::StrokeRoundedRectangle(ID2D1Brush* brush, FLOAT width, FLOAT height, FLOAT strokeWidth, FLOAT radius):
	StrokeRectangle(brush, width, height, strokeWidth), radius(radius)
{
}

StrokeRoundedRectangle::StrokeRoundedRectangle(ID2D1Brush* brush, FLOAT width, FLOAT height, FLOAT radius) :
	StrokeRectangle(brush, width, height), radius(radius)
{
}

StrokeRoundedRectangle::~StrokeRoundedRectangle()
{
}

void StrokeRoundedRectangle::drawStyle(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	assert(brush);
	m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(
		D2D1::RectF(
			x - width / 2,
			y - height / 2,
			x + width / 2,
			y + height / 2),
		radius,
		radius),
		brush, strokeWidth);
}
