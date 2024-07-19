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
	//��� ������Ʈ ������Ʈ4
	for (auto comps : m_ownComponents)
	{
		comps->Update(dt);
	}
	//�ڽ� ���� ������Ʈ�ϱ�
	for (auto child : m_childObject)
	{
		child->Update(dt);
	}
}

void GameObject::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	//����������Ʈ�� �����ϱ�
	for (auto iter : m_ownComponents)
	{
		if (iter->GetName() == "Renderable")
		{
			iter->Render(pRenderTarget);
		}
	}

	//�ڽ� �ѹ��� �������ֱ�
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
