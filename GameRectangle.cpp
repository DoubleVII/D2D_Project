
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
	assert(brush);

	if (rotate) {
		D2D1_POINT_2F center = D2D1::Point2F(x, y);
		m_pRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Rotation(angle, center)
		);
		m_pRenderTarget->FillRectangle(D2D1::RectF(
			x - width / 2,
			y - height / 2,
			x + width / 2,
			y + height / 2),
			brush.Get());
		m_pRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Rotation(0.f, center)
		);
	}
	else {
		m_pRenderTarget->FillRectangle(D2D1::RectF(
			x - width / 2,
			y - height / 2,
			x + width / 2,
			y + height / 2),
			brush.Get());
	}
	

}
