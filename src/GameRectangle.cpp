
#include "GameRectangle.h"



GameRectangle::GameRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT angle)
	: brush(brush),
	x(x),
	y(y),
	width(width),
	height(height),
	angle(angle),
	rotate(TRUE)
{
	
}

GameRectangle::GameRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height)
	: brush(brush),
	x(x),
	y(y),
	width(width),
	height(height),
	angle(0.f),
	rotate(FALSE)
{
}

GameRectangle::GameRectangle(ID2D1Brush* brush, FLOAT width, FLOAT height)
	: brush(brush),
	x(0),
	y(0),
	width(width),
	height(height),
	angle(0.f),
	rotate(FALSE)
{
}

void GameRectangle::draw(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	assert(m_pRenderTarget);

	if (rotate) {
		D2D1_POINT_2F center = D2D1::Point2F(x + width/2, y + height/2);
		m_pRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Rotation(angle, center)
		);
		drawStyle(m_pRenderTarget);
		m_pRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Identity()
		);
	}
	else {
		drawStyle(m_pRenderTarget);
	}
	

}

void GameRectangle::drawStyle(ID2D1HwndRenderTarget* m_pRenderTarget) {
	assert(brush);
	m_pRenderTarget->FillRectangle(D2D1::RectF(
		x,
		y,
		x + width,
		y + height),
		brush);
}
