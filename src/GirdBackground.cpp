#include "GirdBackground.h"




GirdBackground::GirdBackground(ID2D1Brush* brush)
	:brush(brush)
{
}

GirdBackground::~GirdBackground()
{
}

void GirdBackground::draw(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

	// Draw a grid background.
	int width = static_cast<int>(rtSize.width);
	int height = static_cast<int>(rtSize.height);

	for (int x = 0; x < width; x += 10)
	{
		m_pRenderTarget->DrawLine(
			D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
			D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
			brush,
			0.5f
		);
	}

	for (int y = 0; y < height; y += 10)
	{
		m_pRenderTarget->DrawLine(
			D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
			D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
			brush,
			0.5f
		);
	}
}
