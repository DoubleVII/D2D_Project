#pragma once
#include "Drawable.h"
class GameText :
	public Drawable
{
public:
	GameText(ID2D1Brush* brush, IDWriteTextFormat* textFormat, const wchar_t* text, UINT32 length, FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2);
	virtual ~GameText();
	void draw(ID2D1HwndRenderTarget* m_pRenderTarget);

	void setText(const wchar_t* text) {
		this->text = text;
	}

	LPCTSTR getText() {
		return text;
	}

protected:
	IDWriteTextFormat* textFormat;
	ID2D1Brush* brush;
	LPCTSTR text;
	FLOAT x1, y1, x2, y2;
	UINT32 length;
};

