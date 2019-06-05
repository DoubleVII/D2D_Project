#pragma once
#include <d2d1.h>
#include <wrl/client.h>

class Drawable
{
protected:
	template <class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	Drawable() {};

	virtual void draw(ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget) = 0;

};