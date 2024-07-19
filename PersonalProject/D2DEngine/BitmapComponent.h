#pragma once
#include "RenderComponent.h"
class GameObject;

class BitmapComponent: public RenderComponent
{
public:
	ID2D1Bitmap* m_pBitmap;
	
public:
	BitmapComponent(GameObject* pObject,Camera* pCamera = nullptr);
	
	~BitmapComponent() 
	{
		if (m_pBitmap)
		{
			//m_pBitmap->Release();
			m_pBitmap = nullptr;
		}
	};

	bool SetImage(const std::wstring& strFilePath);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget)override;
};

