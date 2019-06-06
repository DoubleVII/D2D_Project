#pragma once
#include "Drawable.h"
class GirdBackground :
	public Drawable
{
public:
	GirdBackground(ID2D1Brush* brush);
	virtual ~GirdBackground();
	void draw(ID2D1HwndRenderTarget* m_pRenderTarget);

private:
	ID2D1Brush* brush;
};

