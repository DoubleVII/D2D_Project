#include "GameText.h"





GameText::GameText(ID2D1Brush* brush, IDWriteTextFormat* textFormat, const wchar_t* text, UINT32 length, FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2) :
	brush(brush), textFormat(textFormat), text(text), length(length), x1(x1), y1(y1), x2(x2), y2(y2)
{
}

GameText::~GameText()
{
}

void GameText::draw(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	m_pRenderTarget->DrawTextW(
		text,
		length,
		textFormat,
		D2D1::RectF(x1, y1, x2, y2),
		brush
	);
}
