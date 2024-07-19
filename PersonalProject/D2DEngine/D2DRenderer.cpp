#include "pch.h"
#include "D2DRenderer.h"


ID2D1HwndRenderTarget* D2DRenderer::m_pRenderTarget = nullptr;

D2DRenderer::D2DRenderer()
{
	
}

D2DRenderer::~D2DRenderer()
{
}

HRESULT D2DRenderer::Initialize(HWND hwnd)
{
	m_hWnd = hwnd;

	HRESULT hr = S_OK;
	hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
	}

	//about frame
	if (SUCCEEDED(hr))
	{
		// Create DXGI factory
		hr = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&m_pDXGIFactory);
	}

	if (SUCCEEDED(hr))
	{
		m_pDXGIFactory->EnumAdapters(0, reinterpret_cast<IDXGIAdapter**>(&m_pDXGIAdapter));
	}

	if (SUCCEEDED(hr))
	{ 
		m_clientSize = CalculateSizeByHwndRect();
		hr = m_pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hWnd, m_clientSize/*D2D1_PRESENT_OPTIONS_IMMEDIATELY*/),
			&m_pRenderTarget
		);
	}

	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_pWICFactory)
		);
	}

	return hr;
}

void D2DRenderer::Uninitialize()
{
	m_pRenderTarget->Release();
	CoUninitialize();
}


HRESULT D2DRenderer::CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap)
{
	HRESULT hr;
	// Create a decoder
	IWICBitmapDecoder* pDecoder = NULL;
	IWICFormatConverter* pConverter = NULL;

	hr = m_pWICFactory->CreateDecoderFromFilename(
		szFilePath,                      // Image to be decoded
		NULL,                            // Do not prefer a particular vendor
		GENERIC_READ,                    // Desired read access to the file
		WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
		&pDecoder                        // Pointer to the decoder
	);

	// Retrieve the first frame of the image from the decoder
	IWICBitmapFrameDecode* pFrame = NULL;
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}

	//Step 3: Format convert the frame to 32bppPBGRA
	if (SUCCEEDED(hr))
	{
		hr =m_pWICFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pFrame,                          // Input bitmap to convert
			GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
			WICBitmapDitherTypeNone,         // Specified dither pattern
			NULL,                            // Specify a particular palette 
			0.f,                             // Alpha threshold
			WICBitmapPaletteTypeCustom       // Palette translation type
		);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, ppID2D1Bitmap);
	}
	// 파일을 사용할때마다 다시 만든다.
	if (pConverter)
		pConverter->Release();

	if (pDecoder)
		pDecoder->Release();

	if (pFrame)
		pFrame->Release();

	return hr;
}

D2D_SIZE_U D2DRenderer::CalculateSizeByHwndRect()
{
	RECT rc;
	::GetClientRect(m_hWnd, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left + 1,
		rc.bottom - rc.top + 1
	);

	return size;
}

void D2DRenderer::FillRectangle(ID2D1RenderTarget* pRenderTarget, D2D1_RECT_F rect, D2D1_COLOR_F color)
{
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrush);
	m_pBrush->SetColor(color);
	pRenderTarget->FillRectangle(rect, m_pBrush);
}

void D2DRenderer::DrawRectangle(ID2D1RenderTarget* pRenderTarget, D2D1_RECT_F rect, D2D1_COLOR_F color,FLOAT width)
{
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrush);
	m_pBrush->SetColor(color);
	pRenderTarget->DrawRectangle(rect, m_pBrush,width);
}

void D2DRenderer::DrawEllipse(ID2D1RenderTarget* pRenderTarget, D2D1_ELLIPSE ellipse, D2D1_COLOR_F color, FLOAT width)
{
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrush);
	m_pBrush->SetColor(color);
	pRenderTarget->DrawEllipse(ellipse, m_pBrush,width);
}

size_t D2DRenderer::GetUsedVRAM()
{
	DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
	m_pDXGIAdapter->QueryVideoMemoryInfo(
		0,
		DXGI_MEMORY_SEGMENT_GROUP_LOCAL,
		&videoMemoryInfo
	);
	return videoMemoryInfo.CurrentUsage / 1024;
}

