#pragma once
#include "RenderComponent.h"

class GameObject;

class TextComponent: public RenderComponent
{
public:
	TextComponent(GameObject* pObject);
	virtual ~TextComponent() {};
public:
	virtual void Update(float dt)override {};
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget)override;
	/**
	 * @brief setTextFormat -> setText
	 * @param �ۼ��� �ؽ�Ʈ 
	 * @param �ؽ�Ʈ ��Ʈ ����
	 * @param �ؽ�Ʈ �� 
	 */
	void SetText(const std::wstring write, float left, float top, float rigth, float bottom, D2D1_COLOR_F brushColor);
	/**
	 * @brief ��Ʈ ����.
	 * @param fontName 
	 * @param fontSize 
	 */
	void SetTextFormat(const std::wstring& fontName,const float& fontSize);
	void WriteText(ID2D1RenderTarget* pRenderTarget, const std::wstring& string, D2D1_RECT_F rect, D2D1_COLOR_F color);

	ID2D1SolidColorBrush* GetBrush() const { return m_pBrush; }

private:
	//brush
	ID2D1SolidColorBrush* m_pBrush;
	//about text
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pDWriteTextFormat;


	std::wstring m_write;
	D2D1_RECT_F m_writeRect;
	D2D1_COLOR_F m_brushColor;

};

