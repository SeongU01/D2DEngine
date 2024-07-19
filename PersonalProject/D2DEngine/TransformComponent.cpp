#include "pch.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Transform.h"

TransformComponent::TransformComponent(GameObject* pObject)
	:Component(pObject,"Transform"), transform(pObject->transform)
{
}


void TransformComponent::Update(float dt)
{
	transform->m_relativeTransform =
		D2D1::Matrix3x2F::Scale(D2D1::SizeF(transform->GetScale().x,transform->GetScale().y)) *
		D2D1::Matrix3x2F::Rotation(transform->GetRotation()) *
		D2D1::Matrix3x2F::Translation(transform->GetLocation().x,transform->GetLocation().y);

	if (m_pObject->GetParent() != nullptr)
	{
		transform->m_worldTransform = transform->m_relativeTransform
			* m_pObject->GetParent()->transform->m_worldTransform;
	}
	else
		transform->m_worldTransform = transform->m_relativeTransform;
}

void TransformComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
}
