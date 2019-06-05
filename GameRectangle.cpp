
#include "GameRectangle.h"



GameRectangle::GameRectangle(ComPtr<ID2D1Brush> brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT angle)
	: brush(brush),
	x(x),
	y(y),
	width(width),
	height(height),
	angle(angle),
	rotate(TRUE)
{
	
}

GameRectangle::GameRectangle(ComPtr<ID2D1Brush> brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height)
	: brush(brush),
	x(x),
	y(y),
	width(width),
	height(height),
	angle(0.f),
	rotate(FALSE)
{
}

GameRectangle::GameRectangle(ComPtr<ID2D1Brush> brush, FLOAT width, FLOAT height)
	: brush(brush),
	x(width/2),
	y(height/2),
	width(width),
	height(height),
	angle(0.f),
	rotate(FALSE)
{
}

void GameRectangle::draw(ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget)
{
	assert(m_pRenderTarget);

	if (rotate) {
		D2D1_POINT_2F center = D2D1::Point2F(x, y);
		m_pRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Rotation(angle, center)
		);
		drawStyle(m_pRenderTarget);
		m_pRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Rotation(0.f, center)
		);
	}
	else {
		drawStyle(m_pRenderTarget);
	}
	

}

void GameRectangle::drawStyle(ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget) {
	assert(brush);
	m_pRenderTarget->FillRectangle(D2D1::RectF(
		x - width / 2,
		y - height / 2,
		x + width / 2,
		y + height / 2),
		brush.Get());
}
