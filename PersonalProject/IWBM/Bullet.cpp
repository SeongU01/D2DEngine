#include "pch.h"
#include "Bullet.h"
#include "../D2DEngine/Transform.h"
//component
#include "../D2DEngine/TransformComponent.h"
#include "../D2DEngine/AnimationComponent.h"
#include "../D2DEngine/ColliderComponent.h"
#include "../D2DEngine/MovementComponent.h"

#include "../D2DEngine/AnimationAsset.h"
#include "../D2DEngine/FSM.h"

#ifndef NDEBUG
#include "../D2DEngine/DebugConsole.h"
#endif // !NDEBUG
Bullet::Bullet(int direction, std::shared_ptr<Camera> camera)
	:GameObject(camera),bulletDirection((Direction)direction),velocity(1150.f)
{
	//animation component
	bulletAnim = new AnimationComponent(this);
	bulletAnim->LoadAnimationAsset(L"../Resource/Animation/Bullet/ken.png");
	bulletAnim->LoadAnimationInfo(L"../Resource/Animation/Bullet/BulletAnim.csv");
	if(bulletDirection==LEFT)
		bulletAnim->SetAnimation("Idle", true);
	else if(bulletDirection==RIGHT)
		bulletAnim->SetAnimation("Idle", false);
	//collider component
	collider = new ColliderComponent(this);
	collider->SetColliderRect(
		D2D_RECT_F{
			0,0,30,32
		}
	);
	//movement component
	movement = new MovementComponent(this);
}

Bullet::~Bullet()
{
}

void Bullet::Update(float dt)
{
	__super::Update(dt);
	TransformUpdate(dt);
}

void Bullet::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

void Bullet::TransformUpdate(float dt)
{
	if (bulletDirection == RIGHT)
	{
		movement->SetDirection(Vector2F(velocity,0).Normalized());
		movement->SetSpeed(velocity);
	}

	else if (bulletDirection == LEFT)
	{
		movement->SetDirection(Vector2F(-velocity, 0).Normalized());
		movement->SetSpeed(velocity);
	}

}
