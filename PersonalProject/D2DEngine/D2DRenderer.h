#pragma once
#include <dxgi1_4.h>
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"windowscodecs.lib")

class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();


	HRESULT Initialize(HWND hwnd);
	void Uninitialize();

	ID2D1Factory* GetFactory() { return m_pFactory; }
	ID2D1HwndRenderTarget* GetRenderTarget() { return m_pRenderTarget; }
	HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap);
	D2D_SIZE_U CalculateSizeByHwndRect();

	void FillRectangle(ID2D1RenderTarget* pRenderTarget, D2D1_RECT_F rect, D2D1_COLOR_F color);
	void DrawRectangle(ID2D1RenderTarget* pRenderTarget, D2D1_RECT_F rect, D2D1_COLOR_F color, FLOAT width);
	void DrawEllipse(ID2D1RenderTarget* pRenderTarget, D2D1_ELLIPSE ellipse, D2D1_COLOR_F color, FLOAT width);


public:
	ID2D1Factory* m_pFactory = nullptr;
	IWICImagingFactory*m_pWICFactory;

	ID2D1SolidColorBrush* m_pBrush;//각종 rect, 원들을 그려주는 brush
private:
	static ID2D1HwndRenderTarget* m_pRenderTarget;
	HWND m_hWnd;//렌더 타겟 생성 핸들
	D2D_SIZE_U m_clientSize;//렌더 타겟의 크기


	D2D_SIZE_U _clientSize;
public:
	size_t GetUsedVRAM();
	D2D_SIZE_U GetClientSize() { return _clientSize; }
	void SetClientSize(UINT32 width, UINT32 height) { _clientSize.width = width; _clientSize.height = height; }
private:
	//about frame
	IDXGIFactory4* m_pDXGIFactory;		// DXGI팩토리
	IDXGIAdapter3* m_pDXGIAdapter;		// 비디오카드 정보에 접근 가능한 인터페이스
	
};





