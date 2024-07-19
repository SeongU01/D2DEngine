#pragma once
#include "RenderComponent.h"

class GameObject;

class UIComponent:public RenderComponent
{
public:
	UIComponent(GameObject* pObject);
	virtual ~UIComponent();
	
	virtual void Update(float dt)override {};
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget)override;
};
