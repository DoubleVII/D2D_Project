#include "GameApp.h"
#include "d3dUtil.h"
#include "DXTrace.h"



GameApp::GameApp(HINSTANCE hInstance)
	: D2DApp(hInstance)
{
}

GameApp::~GameApp()
{
}

bool GameApp::Init()
{
	if (!D2DApp::Init())
		return false;

	if (!InitResource())
		return false;

	return true;
}

void GameApp::OnResize()
{
	D2DApp::OnResize();
}

void GameApp::UpdateScene(float dt)
{
	
}

void GameApp::DrawScene()
{
	//assert(m_pd3dImmediateContext);
	//assert(m_pSwapChain);

	//static float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };	// RGBA = (0,0,0,255)
	//m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), reinterpret_cast<const float*>(&black));
	//m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//// 绘制立方体
	//m_pd3dImmediateContext->DrawIndexed(36, 0, 0);
	//HR(m_pSwapChain->Present(0, 0));
	HRESULT hr = S_OK;

	if (m_pRenderTarget)
	{

		m_pRenderTarget->BeginDraw();

		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

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
				m_pLightSlateGrayBrush.Get(),
				0.5f
			);
		}

		for (int y = 0; y < height; y += 10)
		{
			m_pRenderTarget->DrawLine(
				D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
				D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
				m_pLightSlateGrayBrush.Get(),
				0.5f
			);
		}

		if (x < 400) {
			++x;
			++y;
		}

		// Draw two rectangles.
		D2D1_RECT_F rectangle1 = D2D1::RectF(
			rtSize.width / 2 - 50.0f + x,
			rtSize.height / 2 - 50.0f + y,
			rtSize.width / 2 + 50.0f + x,
			rtSize.height / 2 + 50.0f + y
		);

		D2D1_RECT_F rectangle2 = D2D1::RectF(
			rtSize.width / 2 - 100.0f,
			rtSize.height / 2 - 100.0f,
			rtSize.width / 2 + 100.0f,
			rtSize.height / 2 + 100.0f
		);

		// Draw a filled rectangle.
		m_pRenderTarget->FillRectangle(&rectangle1, m_pLightSlateGrayBrush.Get());

		// Draw the outline of a rectangle.
		m_pRenderTarget->DrawRectangle(&rectangle2, m_pCornflowerBlueBrush.Get());

		hr = m_pRenderTarget->EndDraw();
	}

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
	}
}


bool GameApp::InitResource()
{
	return true;
}
