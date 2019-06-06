#pragma once
#include <d2d1.h>
#include <wrl/client.h>

class Drawable
{
public:
	Drawable() {};

	virtual void draw(ID2D1HwndRenderTarget* m_pRenderTarget) = 0;

};