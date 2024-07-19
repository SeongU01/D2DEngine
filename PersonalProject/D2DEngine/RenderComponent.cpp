#include "pch.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Camera.h"

RenderComponent::RenderComponent(GameObject* pObject,Camera* pCamera)
	:Component(pObject,"Renderable"),transform(pObject->transform), m_camera(pCamera)
{
	
}

void RenderComponent::Update(float dt)
{
}

void RenderComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	D2D1::Matrix3x2F centerMaxtrix = D2D1::Matrix3x2F::Translation
	(m_center.x, m_center.y);
	D2D1InvertMatrix(&centerMaxtrix);
	transform->m_worldTransform = centerMaxtrix * transform->m_worldTransform;
	pRenderTarget->SetTransform(transform->m_worldTransform);
	if (m_camera)
	{
		transform->m_worldTransform = m_camera->transform->m_worldTransform* transform->m_worldTransform;
	}
}
