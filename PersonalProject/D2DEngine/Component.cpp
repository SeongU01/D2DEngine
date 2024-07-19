#include "pch.h"
#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* pObject, const std::string& name)
	:m_pObject(pObject), m_pName(name)
{
	pObject->AddComponent(this);
}

Component::~Component()
{
}

void Component::Update(float dt)
{
}
