#include "GameRectangle.h"

class RoundedRectangle :public GameRectangle {
public:
	RoundedRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT radius, FLOAT angle);
	RoundedRectangle(ID2D1Brush* brush, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT radius);
	RoundedRectangle(ID2D1Brush* brush, FLOAT width, FLOAT height, FLOAT radius);
	virtual ~RoundedRectangle();
	FLOAT getRadius() {
		return radius;
	}
	void setRadius(FLOAT radius) {
		this->radius = radius;
	}

	void drawStyle(ID2D1HwndRenderTarget* m_pRenderTarget);

private:
	FLOAT radius;
};