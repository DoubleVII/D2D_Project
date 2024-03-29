﻿#pragma once
#include "Drawable.h"
#include <assert.h>

class GameCircle :public Drawable {
public:
	GameCircle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT radius);

	GameCircle(ID2D1Brush* brush, FLOAT radius);

	void draw(ID2D1HwndRenderTarget* m_pRenderTarget);

	void setX(FLOAT x) {
		this->x = x;
	}
	void setY(FLOAT y) {
		this->y = y;
	}

	void setRadius(FLOAT radius) {
		this->radius = radius;
	}

	FLOAT getX() {
		return x;
	}
	FLOAT getY() {
		return y;
	}

	FLOAT getRadius() {
		return radius;
	}


protected:
	FLOAT x, y;
	FLOAT radius;
	ID2D1Brush* brush;

	virtual void drawStyle(ID2D1HwndRenderTarget* m_pRenderTarget);
};