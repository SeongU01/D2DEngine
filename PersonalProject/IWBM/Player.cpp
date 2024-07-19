#include "pch.h"
#include "Player.h"
#include "../D2DEngine/InputSystem.h"
#include "../D2DEngine/Transform.h"
//component
#include "../D2DEngine/TransformComponent.h"
#include "../D2DEngine/AnimationComponent.h"
#include "../D2DEngine/ColliderComponent.h"
#include "../D2DEngine/MovementComponent.h"

#include "../D2DEngine/AnimationAsset.h"
#include "../D2DEngine/FSM.h"
#include "PlayerState.h"


#ifndef NDEBUG
#include "../D2DEngine/DebugConsole.h"
#endif // !NDEBUG

Player::Player(std::shared_ptr<Camera> camera)
	:GameObject(camera),
	isJumping(false), jumpVelocity(0), gravity(1100.f),
	jumpCount(1), downVelocity(0), onGravity(false), moveVelocity(350.f, 0.f)
{
	//animation component
	playerAnim = new AnimationComponent(this);
	playerAnim->LoadAnimationAsset(L"../Resource/Animation/Ken/ken.png");
	playerAnim->LoadAnimationInfo(L"../Resource/Animation/Ken/KenAnim.csv");
	//collider component
	collider = new ColliderComponent(this);
	D2D_RECT_F newRect = {
	 2.625f, 1.925f, 48.125f, 85.25f
	};

	collider->SetColliderRect(newRect);
	//movement
	movement = new MovementComponent(this);
	fsm = new FSM(this);

	fsm->AddState("Idle", new Idle(movement,playerAnim));
	fsm->AddState("Move", new Move(movement,playerAnim));
	fsm->AddState("Jump", new Jump(playerAnim));
	fsm->AddState("Attack", new Attack(playerAnim));
	fsm->SetState("Idle");
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	__super::Update(dt);
	TransformUpdate(dt);

	Debug.Log((int)collider->GetCollisionDetails().first);
}

void Player::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

void Player::TransformUpdate(float dt)
{
	//중력 관련
	if (onGravity)
	{
		Gravity(dt);
	}
	
	//땅이 아닐경우 중력 작동
	if (collider->GetColideWith() != "Ground"&&!isJumping)
	{
		jumpCount = 2;
		onGravity = true;
	}

	bool rightKeyDown = Input::inputManager->IsCurrDn(VK_RIGHT);
	bool leftKeyDown = Input::inputManager->IsCurrDn(VK_LEFT);


	if (rightKeyDown && leftKeyDown)
	{
		 //두 키가 모두 눌린 경우의 처리
		if (currentDirection == RIGHT)
		{
			//왼쪽이동
			movement->SetDirection(Vector2F(-moveVelocity.x, 0).Normalized());
			movement->SetSpeed(moveVelocity.x);
		}
		else if (currentDirection == LEFT)
		{
			//오른쪽 이동
			movement->SetDirection(Vector2F(moveVelocity.x, 0).Normalized());
			movement->SetSpeed(moveVelocity.x);
		}
	}
	else if (rightKeyDown)
	{
		// 오른쪽 키가 눌린 경우
		currentDirection = RIGHT;
		if (!(collider->GetColideWith() == "Ground" && collider->GetCollisionDetails().first == CollisionDirection::Right))
		{
			//오른쪽 이동
			movement->SetDirection(Vector2F(moveVelocity.x, 0).Normalized());
			movement->SetSpeed(moveVelocity.x);
		}
		else
		{
			this->transform->GetLocation().x = collider->GetColideWithRect().left -
				(collider->GetColliderRect().right - collider->GetColliderRect().left) / 2;
		}
	
	}
	else if (leftKeyDown)
	{
		// 왼쪽 키가 눌린 경우
		currentDirection = LEFT;
		if (!(collider->GetColideWith() == "Ground" && collider->GetCollisionDetails().first == CollisionDirection::Left))
		{
			//왼쪽이동
			movement->SetDirection(Vector2F(-moveVelocity.x, 0).Normalized());
			movement->SetSpeed(moveVelocity.x);
		}
		else
		{
			this->transform->GetLocation().x = collider->GetColideWithRect().right + 
				(collider->GetColliderRect().right - collider->GetColliderRect().left) / 2;
		}
	}

	if (Input::inputManager->IsTurnUp(VK_RIGHT) || Input::inputManager->IsTurnUp(VK_LEFT))
	{
		movement->SetSpeed(0.f);
	}
	/*if (Input::inputManager->IsCurrDn(VK_DOWN))
	{
		this->transform->GetLocation().y += dt * 250;
	}
	if (Input::inputManager->IsCurrDn(VK_UP))
	{
		this->transform->GetLocation().y -= dt * 250;
	}*/


	//점프관련
	DoJump(dt);

	//밑에서 부딫힐경우
	if (collider->GetColideWith() == "Ground" && collider->GetCollisionDetails().first == CollisionDirection::Top)
	{
		this->transform->GetLocation().y = collider->GetColideWithRect().bottom +
			((collider->GetColliderRect().bottom - collider->GetColliderRect().top) / 2)+0.01f;

		jumpVelocity = 0;
		//isJumping = false;	
	}
	//땅위일 경우 locationY고정
	if (collider->GetColideWith() == "Ground" && !isJumping && collider->GetCollisionDetails().first==CollisionDirection::Bottom)
	{
		onGravity = false;
		jumpCount = 0;
		downVelocity = 0.f;

		this->transform->GetLocation().y = collider->GetColideWithRect().top-
			(collider->GetColliderRect().bottom - collider->GetColliderRect().top)/2+5;
	}

}

void Player::DoJump(float dt)
{
	//점프 시작
	if (Input::inputManager->IsTurnDn('Z') && jumpCount < 2)
	{
		isJumping = true;
		jumpVelocity =	500.f; // 점프 시작 시 초기 속도 설정
		jumpCount++; // 점프 횟수 증가
	}

	//점프 도중
	if (isJumping)
	{
		this->transform->GetLocation().y -= jumpVelocity * dt; // 점프하는 로직 y값 변경
		jumpVelocity -= gravity * dt; // 중력의 영향을 받음

		// 점프가 끝났을 때
		if (jumpVelocity <= 0 && collider->GetColideWith() == "Ground"&& collider->GetCollisionDetails().first == CollisionDirection::Bottom)
		{
			isJumping = false;
			jumpCount = 0; // 땅에 닿으면 점프 횟수 초기화
		}
	}
}

void Player::Gravity(float dt)
{
	downVelocity -= gravity * dt;
	this->transform->GetLocation().y -= downVelocity * dt; // 중력의 영향을 받아 y값 변경
}

