#pragma once
#include "Transform.h"
#include "Component.h"

class GameObject;
class Camera;

class RenderComponent:public Component
{
public:
	RenderComponent(GameObject* pObject, Camera* pCamera = nullptr);
	virtual ~RenderComponent() {};

public:
	D2D1_VECTOR_2F m_center;
	Transform* transform;
	Camera* m_camera;

public:
	virtual void Update(float dt);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
	bool culling();
};

