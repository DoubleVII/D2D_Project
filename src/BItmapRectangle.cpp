﻿#include "BItmapRectangle.h"





BitmapRectangle::BitmapRectangle(ID2D1Bitmap* pBitmap, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT angle)
	:GameRectangle(nullptr, x, y, width, height, angle), pBitmap(pBitmap), opacity(1.f)
{
}

BitmapRectangle::BitmapRectangle(ID2D1Bitmap* pBitmap, FLOAT x, FLOAT y, FLOAT width, FLOAT height)
	: GameRectangle(nullptr, x, y, width, height), pBitmap(pBitmap), opacity(1.f)
{
}

BitmapRectangle::BitmapRectangle(ID2D1Bitmap* pBitmap, FLOAT width, FLOAT height)
	: GameRectangle(nullptr, width, height), pBitmap(pBitmap), opacity(1.f)
{
}

BitmapRectangle::~BitmapRectangle()
{
}

void BitmapRectangle::drawStyle(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	m_pRenderTarget->DrawBitmap(pBitmap, D2D1::RectF(
		x,
		y,
		x + width,
		y + height),
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
}
