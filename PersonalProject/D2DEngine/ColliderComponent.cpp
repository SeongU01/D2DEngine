#include "pch.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Transform.h"
#ifndef NDEBUG
#endif // !NDEBUG
#include "DebugConsole.h"
#include "Camera.h"

ColliderComponent::ColliderComponent(GameObject* pObject)
	:Component(pObject, "Collider"), m_onCollider(false),m_colideWith("None")
{
	m_colliderAABB = new AABB;
}

void ColliderComponent::Update(float dt)
{
	for (auto iter : m_checkColliders)
	{
		if(iter.first!=NULL)
		{
			m_onCollider = m_colliderAABB->CheckIntersect(*iter.first);
			collisionDetails = m_colliderAABB->CheckIntersectionDetails(*iter.first);
			if (m_onCollider)
			{
				m_colideWith = iter.second;
				m_colideWithRect = iter.first->GetRect();
				/*Debug.Log(iter.first.GetRect().top);
				Debug.Log(iter.first.GetRect().bottom);*/
				/*Debug.Log("first");
				Debug.Log((int)collisionDetails.first);
				Debug.Log("second");
				Debug.Log((int)collisionDetails.second)*/;
				break;
			}
			else
			{
				m_colideWith = "None";
			}
		}
	}

	SetColliderRect(m_colliderRect);
}

void ColliderComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	
}

void ColliderComponent::SetColliderRect(D2D_RECT_F rect)
{
	m_colliderRect = rect;
	
	if (dynamic_cast<Camera*>(m_pObject))
	{
		m_colliderAABB->SetCenter(
			m_pObject->transform->GetLocation().x+ (rect.right - rect.left) / 2,
			m_pObject->transform->GetLocation().y+(rect.bottom - rect.top) / 2
		);
		
		m_colliderAABB->SetExtent((rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2);
		m_colliderAABB->SetAABBRect();
	}
	else
	{
		m_colliderAABB->SetCenter(
			m_pObject->transform->GetLocation().x,
			m_pObject->transform->GetLocation().y
		);
		m_colliderAABB->SetExtent((rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2);
		m_colliderAABB->SetAABBRect();
	}
}


void ColliderComponent::AddCheckColliderList(AABB* aabb, std::string objectName)
{
	std::pair<AABB*, std::string> colliderPair = { aabb,objectName };
	m_checkColliders.push_back(colliderPair);
}
