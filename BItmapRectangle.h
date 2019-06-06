#pragma once
#include "GameRectangle.h"
class BitmapRectangle :
	public GameRectangle
{
public:
	BitmapRectangle(ID2D1Bitmap* pBitmap, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT angle);
	BitmapRectangle(ID2D1Bitmap* pBitmap, FLOAT x, FLOAT y, FLOAT width, FLOAT height);
	BitmapRectangle(ID2D1Bitmap* pBitmap, FLOAT width, FLOAT height);
	virtual ~BitmapRectangle();

	void setOpacity(FLOAT opacity) {
		this->opacity = opacity;
	}

	FLOAT getOpacity(){
		return opacity;
	}

protected:
	ID2D1Bitmap* pBitmap;
	FLOAT opacity;

	void drawStyle(ID2D1HwndRenderTarget* m_pRenderTarget);
};

