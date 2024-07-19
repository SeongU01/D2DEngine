#include "pch.h"
#include "GameObject.h"
#include "TextComponent.h"

TextComponent::TextComponent(GameObject* pObject)
	:RenderComponent(pObject)
{
	HRESULT hr=S_OK;
	//about text
	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	}
}

void TextComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	WriteText(pRenderTarget, m_write, m_writeRect, m_brushColor);
}

void TextComponent::SetText(const std::wstring write, float left, float top, float right, float bottom, D2D1_COLOR_F brushColor)
{
	m_write = write;
	m_writeRect.left = left;
	m_writeRect.right = right;
	m_writeRect.top = top;
	m_writeRect.bottom = bottom;
	
	m_brushColor = brushColor;
}

void TextComponent::SetTextFormat(const std::wstring& fontName, const float& fontSize)
{
	HRESULT hr = S_OK;

	if (SUCCEEDED(hr))
	{
		// DirectWrite 텍스트 형식 개체를 만듭니다.
		hr = m_pDWriteFactory->CreateTextFormat(
			fontName.c_str(), // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			fontSize,   // Font Size
			L"", //locale
			&m_pDWriteTextFormat
		);
	}
}

void TextComponent::WriteText(ID2D1RenderTarget* pRenderTarget, const std::wstring& string, D2D1_RECT_F rect, D2D1_COLOR_F color)
{
	pRenderTarget->CreateSolidColorBrush(color,&m_pBrush);
	m_pBrush->SetColor(color);
	pRenderTarget->DrawTextW(string.c_str(), (UINT32)string.length(), m_pDWriteTextFormat, rect, m_pBrush);
}



