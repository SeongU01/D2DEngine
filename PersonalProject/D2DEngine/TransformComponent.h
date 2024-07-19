#pragma once
#include "Component.h"

class GameObject;
class Transform;

class TransformComponent:public Component
{
public:
	TransformComponent(GameObject* pObject);
	virtual ~TransformComponent() {};
public:
	Transform* transform;
	virtual void Update(float dt)override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget)override;
	
};

