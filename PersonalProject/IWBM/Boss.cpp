#include "pch.h"
#include "Boss.h"
#include "../D2DEngine/InputSystem.h"
#include "../D2DEngine/Transform.h"
//component
#include "../D2DEngine/TransformComponent.h"
#include "../D2DEngine/AnimationComponent.h"
#include "../D2DEngine/ColliderComponent.h"
#include "../D2DEngine/MovementComponent.h"

#include "../D2DEngine/AnimationAsset.h"
#include "../D2DEngine/FSM.h"

#include "../D2DEngine/EventManager.h"

//state
#include "BossState.h"

//gameObject
#include "Bullet.h"

#ifndef NDEBUG
#include "../D2DEngine/DebugConsole.h"
#endif // !NDEBUG

Boss::Boss(std::shared_ptr<Camera>camera)
	:GameObject(camera)
{
	bossAnim = new AnimationComponent(this);
	collider = new ColliderComponent(this);
	movement = new MovementComponent(this);
	//bossAnim->LoadAnimationAsset(L"../Resource/Stage1/kitty/explosion.png");
	bossAnim->LoadAnimationAsset(L"../Resource/Stage1/kitty/kitty.png");
	bossAnim->LoadAnimationInfo(L"../Resource/Stage1/kitty/kittyAnim.csv");
	
	D2D_RECT_F newRect;
	newRect = {
		20.f,100.f,140.f,300.f
	};
	collider->SetColliderRect(newRect);

	fsm = new FSM(this);
	fsm->AddState("Idle",new BossMove(movement, bossAnim));
	fsm->AddState("Dead", new BossDead(movement, bossAnim));
	fsm->SetState("Idle");


	SubscribeToEvents();
}

Boss::~Boss()
{
}

void Boss::Update(float dt)
{
	__super::Update(dt);
	_HpBar= { 0,0,GetHp(),20 };
	if (_HP <= 0)
	{
		if(!isDead)
		{
			isDead = true;
			fsm->SetState("Dead");
		}
	}

}

void Boss::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

void Boss::Damaged()
{
	_HP -= 28;
	//Debug.Log(_HP);
}

void Boss::SubscribeToEvents()
{
	// 이벤트 등록
	EventManager::GetInstance().RegisterEvent(L"BossDamaged");
	EventManager::GetInstance().RegisterEvent(L"BossDead");

	// 이벤트 구독
	EventManager::GetInstance().Subscribe<>(L"BossDamaged", std::function<void()>(std::bind(&Boss::Damaged, this)));
	
}