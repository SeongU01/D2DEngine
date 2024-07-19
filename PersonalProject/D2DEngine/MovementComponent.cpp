#include "pch.h"
#include "MovementComponent.h"
#include "Transform.h"
#include "GameObject.h"

MovementComponent::MovementComponent(GameObject* pObject)
	:Component(pObject,"Movement")
{
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::Update(float dt)
{
	m_pObject->transform->GetLocation() += _direction * _speed * dt;
}

