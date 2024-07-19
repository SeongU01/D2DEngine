#include "pch.h"
#include "BossState.h"

#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/AnimationComponent.h"
#include "../D2DEngine/MovementComponent.h" 
#include "../D2DEngine/ColliderComponent.h" 
#include "../D2DEngine/InputSystem.h"
#include "../D2DEngine/FSM.h"
#include "../D2DEngine/EventManager.h"

#include "../D2DEngine/InputSystem.h"

//------------------------idle----------------------------//
void BossMove::Enter()
{
	animation->SetAnimation("Idle", animation->m_bMirror);
	movement->SetDirection(Vector2F(0, 1.0).Normalized());
	movement->SetSpeed(0.f);
}

void BossMove::Update(float dt)
{
	TransformUpdate(dt);
}

void BossMove::Exit()
{
}

void BossMove::TransformUpdate(float dt)
{
	_time += dt;
	float speed =( _downY-_upY) * std::sin((2*M_PI) * (_time / _duration));
	movement->SetSpeed(speed);

	if (_time >= _duration)
	{
		_time = 0.f;
	}
	
	if (Input::inputManager->IsTurnDn(VK_SPACE))
	{
		GetOwner()->SetState("Dead");
	}
}

void BossDead::Enter()
{
	movement->SetSpeed(0.f);
	animation->LoadAnimationAsset(L"../Resource/Stage1/kitty/explosion.png");
	animation->SetAnimation("Dead", animation->m_bMirror);
}

void BossDead::Update(float dt)
{
	if (animation->m_onAnimationEnd)
	{
		EventManager::GetInstance().Emit<>(L"BossDeadEnd");
	}
}

void BossDead::Exit()
{
}
