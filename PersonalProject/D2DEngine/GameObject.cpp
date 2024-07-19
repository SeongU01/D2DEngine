#include "pch.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Component.h"
#include "Transform.h"
#include "Camera.h"
#include "FSM.h"
//#include "BitmapComponent.h"

GameObject::GameObject(std::shared_ptr<Camera> camera)
	:pCamera(camera)
{

	transform =new Transform();
	new TransformComponent(this);
}

GameObject::~GameObject()
{
	if(!m_childObject.empty())
	{
		for (auto& iter : m_childObject)
		{
			delete iter;
		}
	}

	for (auto& iter : m_ownComponents)
	{
		delete iter;
	}
	m_ownComponents.clear();

	delete transform;
}

void GameObject::Update(float dt)
{
	//모든 컴포넌트 업데이트4
	for (auto comps : m_ownComponents)
	{
		comps->Update(dt);
	}
	//자식 까지 업데이트하기
	for (auto child : m_childObject)
	{
		child->Update(dt);
	}
}

void GameObject::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	//렌더컴포넌트만 렌더하기
	for (auto iter : m_ownComponents)
	{
		if (iter->GetName() == "Renderable")
		{
			iter->Render(pRenderTarget);
		}
	}

	//자식 한번에 렌더해주기
	for (auto child : m_childObject)
	{
		child->Render(pRenderTarget);
	}
}

Component* GameObject::AddComponent(Component* pComponent)
{
	if (pComponent != nullptr)
	{
		m_ownComponents.push_back(pComponent);
	}
	return pComponent;
}

Component* GameObject::GetComponent(const std::string& compName)
{
	for (auto& pComp : m_ownComponents)
	{
		if (pComp->GetName()==compName)
		{
			return pComp;
		}
	}
}
