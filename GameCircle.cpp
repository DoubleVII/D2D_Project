#include "GameCircle.h"

GameCircle::GameCircle(ComPtr<ID2D1Brush> brush, FLOAT x, FLOAT y, FLOAT radius)
	:brush(brush),
	x(x),
	y(y),
	radius(radius)
{
}

GameCircle::GameCircle(ComPtr<ID2D1Brush> brush, FLOAT radius)
	:brush(brush),
	x(radius/2),
	y(radius / 2),
	radius(radius)
{
}

void GameCircle::draw(ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget)
{
	assert(m_pRenderTarget);
	assert(brush);

	drawStyle(m_pRenderTarget);
}

void GameCircle::drawStyle(ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget)
{
	m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush.Get());
}
