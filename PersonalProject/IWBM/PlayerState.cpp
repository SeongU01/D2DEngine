#include "pch.h"
#include "PlayerState.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/AnimationComponent.h"
#include "../D2DEngine/MovementComponent.h" 
#include "../D2DEngine/InputSystem.h"
#include "../D2DEngine/FSM.h"
#include "../D2DEngine/AnimationAsset.h"


//------------------------idle----------------------------//

void Idle::Enter()
{
  animation->SetAnimation("Idle",animation->m_bMirror);
  movement->SetDirection(Vector2F(0, 0).Normalized());
  movement->SetSpeed(0);
  
}

void Idle::Update(float dt)
{
  // 예시: 이동 키를 누르면 Move 상태로 전환
  if (Input::inputManager->IsCurrDn(VK_RIGHT) || Input::inputManager->IsCurrDn(VK_LEFT))
  {
   GetOwner()->SetState("Move");
  }
  
  // 예시: 점프 키를 누르면 Jump 상태로 전환
  else if (Input::inputManager->IsTurnDn('Z'))
  {
    GetOwner()->SetState("Jump");
  
  }
  else if (Input::inputManager->IsCurrDn('X'))
  {
    GetOwner()->SetState("Attack");
  }
}

void Idle::Exit()
{
}

//------------------------move----------------------------//

void Move::Enter()
{
  animation->SetAnimation("Move",animation->m_bMirror);
}

void Move::Update(float dt)
{
  // 예시: 이동 키를 떼면 Idle 상태로 전환
 /* if (!Input::inputManager->IsCurrDn(VK_RIGHT) && !Input::inputManager->IsCurrDn(VK_LEFT))
  {
    animComp->GetOwner()->m_FSM->SetState("Idle", animComp, animComp->m_bMirror);
  }*/
  // 예시: 점프 키를 누르면 Jump 상태로 전환
  RightAnim(dt);
  LeftAnim(dt);
  if (Input::inputManager->IsTurnDn('Z'))
  {
    GetOwner()->SetState("Jump");
  }

  if (Input::inputManager->IsCurrDn('X'))
  {
    GetOwner()->SetState("Attack");
  }
}

void Move::Exit()
{
}

void Move::RightAnim(float dt)
{

  if (Input::inputManager->IsCurrDn(VK_RIGHT))
  {
    
    if (Input::inputManager->IsCurrDn(VK_LEFT))
    {
      // 둘 다 눌린 경우에는 이동 방향을 현재 방향으로 유지합니다.
      if (animation->m_pAnimationInfo->name != "Move" && animation->m_pAnimationInfo->name != "Jump")
       GetOwner()->SetState("Move");
      return;
    }

    currentDirection = RIGHT;
    animation->m_bMirror = false;
    if (animation->m_pAnimationInfo->name != "Move" && animation->m_pAnimationInfo->name != "Jump")
      GetOwner()->SetState("Move");
  }

  //키 때면
  if (Input::inputManager->IsTurnUp(VK_RIGHT))
  {
    if (currentDirection == RIGHT && animation->m_pAnimationInfo->name != "Jump")
      GetOwner()->SetState("Idle");
  }
}

void Move::LeftAnim(float dt)
{
  if (Input::inputManager->IsCurrDn(VK_LEFT))
  {
  
    if (Input::inputManager->IsCurrDn(VK_RIGHT))
    {
      // 둘 다 눌린 경우에는 이동 방향을 현재 방향으로 유지합니다.
      if (animation->m_pAnimationInfo->name != "Move" && animation->m_pAnimationInfo->name != "Jump")
        GetOwner()->SetState("Move");
      return;
    }

    currentDirection = LEFT;
    animation->m_bMirror = true;
    if (animation->m_pAnimationInfo->name != "Move" && animation->m_pAnimationInfo->name != "Jump")
      GetOwner()->SetState("Move");
  }

  //키 떄면
  if (Input::inputManager->IsTurnUp(VK_LEFT))
  {
    if (currentDirection == LEFT && animation->m_pAnimationInfo->name != "Jump")
     GetOwner()->SetState("Idle");
  }
}

//------------------------jump----------------------------//

void Jump::Enter()
{
  animation->SetAnimation("Jump",animation->m_bMirror);
  animation->m_pAnimationInfo->SetNextAnimInfo("Idle");
}

void Jump::Update(float dt)
{
  bool rightKeyDown = Input::inputManager->IsCurrDn(VK_RIGHT);
  bool leftKeyDown = Input::inputManager->IsCurrDn(VK_LEFT);

  
  if (rightKeyDown && leftKeyDown)
  {
    // 두 키가 모두 눌린 경우의 처리
    if (currentDirection == RIGHT)
    {
      animation->m_bMirror = false;
    }
    else if (currentDirection == LEFT)
    {
      animation->m_bMirror = true;
    }
  }
  else if (rightKeyDown)
  {
    // 오른쪽 키가 눌린 경우
    animation->m_bMirror = false;
  }
  else if (leftKeyDown)
  {
    // 왼쪽 키가 눌린 경우
    animation->m_bMirror = true;
  }


  //프레임 애니메이션 프레임 끝나면
  if (animation->m_onAnimationEnd)
  {
    GetOwner()->SetState("Idle");
  }
}

void Jump::Exit()
{
  animation->SetAnimationEndAfterLastFrame(false);
}

//------------------------Attack----------------------------//

void Attack::Enter()
{
  animation->SetAnimation("Attack", animation->m_bMirror);
  animation->m_pAnimationInfo->SetNextAnimInfo("Idle");
}

void Attack::Update( float dt)
{
  bool rightKeyDown = Input::inputManager->IsCurrDn(VK_RIGHT);
  bool leftKeyDown = Input::inputManager->IsCurrDn(VK_LEFT);


  if (rightKeyDown && leftKeyDown)
  {
    // 두 키가 모두 눌린 경우의 처리
    if (currentDirection == RIGHT)
    {
      animation->m_bMirror = false;
    }
    else if (currentDirection == LEFT)
    {
      animation->m_bMirror = true;
    }
  }
  else if (rightKeyDown)
  {
    // 오른쪽 키가 눌린 경우
    animation->m_bMirror = false;
  }
  else if (leftKeyDown)
  {
    // 왼쪽 키가 눌린 경우
    animation->m_bMirror = true;
  }


  //프레임 애니메이션 프레임 끝나면
  if (animation->m_onAnimationEnd)
  {
    GetOwner()->SetState("Idle");
  }
}

void Attack::Exit()
{
  animation->SetAnimationEndAfterLastFrame(false);
}


