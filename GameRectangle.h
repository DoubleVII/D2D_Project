#pragma once
#include "Drawable.h"
#include <assert.h>

class GameRectangle :public Drawable {
public:
	GameRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT angle);

	GameRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height);

	GameRectangle(ID2D1Brush* brush, FLOAT width, FLOAT height);

	void draw(ID2D1HwndRenderTarget* m_pRenderTarget);

	void setX(FLOAT x) {
		this->x = x;
	}
	void setY(FLOAT y) {
		this->y = y;
	}
	void setAngle(FLOAT angle) {
		rotate = TRUE;
		this->angle = angle;
	}
	void setWidth(FLOAT width) {
		this->width = width;
	}
	void setHeight(FLOAT height) {
		this->height = height;
	}
	
	FLOAT getX() {
		return x;
	}
	FLOAT getY() {
		return y;
	}
	FLOAT getAngle() {
		return angle;
	}
	BOOL isRotate() {
		return rotate;
	}
	FLOAT getWidth() {
		return width;
	}
	FLOAT getHeight() {
		return height;
	}
	

protected:
	FLOAT x, y;
	FLOAT width, height;
	FLOAT angle;
	BOOL rotate;
	ID2D1Brush* brush;

	virtual void drawStyle(ID2D1HwndRenderTarget* m_pRenderTarget);
};