#include "GameLine.h"





GameLine::GameLine(ID2D1Brush* brush, FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT stroke) :
	brush(brush), x1(x1), y1(y1), x2(x2), y2(y2), strock(stroke)
{
}

GameLine::GameLine(ID2D1Brush* brush, FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2) :
	brush(brush), x1(x1), y1(y1), x2(x2), y2(y2), strock(1.f)
{
}

GameLine::~GameLine()
{
}

void GameLine::draw(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	m_pRenderTarget->DrawLine(
		D2D1::Point2F(x1, y1),
		D2D1::Point2F(x2, y2),
		brush,
		strock
	);
}
