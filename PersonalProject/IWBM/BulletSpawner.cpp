#include "pch.h"
#include "BulletSpawner.h"

#include "../D2DEngine/SceneGraph.h"

//component
#include "../D2DEngine/ColliderComponent.h"

#include "../D2DEngine/InputSystem.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/Camera.h"

#include "../D2DEngine/EventManager.h"

//gameobject
#include "Boss.h"
#include "Bullet.h"


BulletSpawner::BulletSpawner(GameObject* pParent)
{
	this->SetParent(pParent);
	collider = new ColliderComponent(this);
	this->transform->SetLocation(50, 0);

}

BulletSpawner::~BulletSpawner()
{
	if (!bullets.empty())
	{
		for (auto &iter : bullets)
		{
			delete iter;
		}
	}
}

void BulletSpawner::Update(float dt)
{
	__super::Update(dt);
	//총알들 업데이트는 스포너가 관리
	for (auto iter :bullets)
	{
		iter->Update(dt);

	}
	BulletUpdate();
	ColliderUpdate();
	DirectionUpdate();
	BulletFire(dt);

	//TriggerBossDamaged();
#ifndef NDEBUG
	//Debug.Log((int)currentDirection);

#endif // !NDEBUG

}

void BulletSpawner::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

void BulletSpawner::BulletUpdate()
{
	for (auto iter = bullets.begin(); iter != bullets.end(); )
	{
		//화면 밖에 나가면 콜리이드는 무조건 false
		if ((*iter)->GetCollider()->GetColideWith()=="Boss")
		{
			delete* iter;
			iter = bullets.erase(iter);
			EventManager::GetInstance().Emit<>(L"BossDamaged");
		}
		else
		{
			++iter;
		}
	}


	for (auto iter = bullets.begin(); iter != bullets.end(); )
	{
		//화면 밖에 나가면 콜리이드는 무조건 false
		if ((*iter)->GetCollider()->GetColideWith()!="Camera")
		{
			delete* iter;
			iter = bullets.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void BulletSpawner::BulletFire(float dt)
{
	fireDelay += dt;
	if (Input::inputManager->IsCurrDn('X') && bullets.size() < 5&&currentDirection==RIGHT)
	{
		if (fireDelay >= 0.1f)
		{
			fireDelay = 0;
			Bullet* bullet = new Bullet(RIGHT, m_pParentObject->pCamera);
			bullet->transform->SetLocation(
				m_pParentObject->transform->GetLocation().x+this->transform->GetLocation().x,
				m_pParentObject->transform->GetLocation().y+this->transform->GetLocation().y);

			if (bossCol != nullptr)
			{
				bullet->GetCollider()->AddCheckColliderList(bossCol->GetCollider(), "Boss");
			}
			for (auto iter : currSceneObjectCollider)
			{
				bullet->GetCollider()->AddCheckColliderList(iter->GetCollider(),"OtherObject");
			}
			bullet->GetCollider()->AddCheckColliderList(bullet->pCamera->m_cameraCollider->GetCollider(),"Camera");
			bullets.push_back(bullet);
		}
	}
	else if (Input::inputManager->IsCurrDn('X') && bullets.size() < 5 && currentDirection == LEFT)
	{
		if (fireDelay >= 0.1f)
		{
			fireDelay = 0;
			Bullet* bullet = new Bullet(LEFT, m_pParentObject->pCamera);
			bullet->transform->SetLocation(
				m_pParentObject->transform->GetLocation().x - this->transform->GetLocation().x,
				m_pParentObject->transform->GetLocation().y - this->transform->GetLocation().y);
			if (bossCol != nullptr)
			{
				bullet->GetCollider()->AddCheckColliderList(bossCol->GetCollider(), "Boss");
			}
			for (auto iter : currSceneObjectCollider)
			{
				bullet->GetCollider()->AddCheckColliderList(iter->GetCollider(), "OtherObject");
			}
			bullet->GetCollider()->AddCheckColliderList(bullet->pCamera->m_cameraCollider->GetCollider(), "Camera");
			bullets.push_back(bullet);
		}
	}
}

void BulletSpawner::ColliderUpdate()
 {
	D2D_RECT_F newRect = {
	 2.625f, 1.925f, 48.125f, 10.25f
	};
	collider->SetColliderRect(newRect);
}

void BulletSpawner::DirectionUpdate()
{
	bool rightKeyDown = Input::inputManager->IsCurrDn(VK_RIGHT);
	bool leftKeyDown = Input::inputManager->IsCurrDn(VK_LEFT);
	if (rightKeyDown && leftKeyDown)
	{
		if (currentDirection == RIGHT)
		{
			
			currentDirection = RIGHT;
		}
		else if (currentDirection == LEFT)
		{
			currentDirection = LEFT;
		}
	}
	else if (rightKeyDown)
	{
		// 오른쪽 키가 눌린 경우
		currentDirection = RIGHT;
	}
	else if (leftKeyDown)
	{
		// 왼쪽 키가 눌린 경우
		currentDirection = LEFT;
	}

}

void BulletSpawner::SetBulletColiiderInteration(ColliderComponent* _collider)
{
	currSceneObjectCollider.push_back(_collider);
}

void BulletSpawner::TriggerBossDamaged()
{
	//EventManager::GetInstance().Emit<>(L"BossDamaged");
	EventManager& em = EventManager::GetInstance();
	em.Emit<>(L"BossDamaged");
}