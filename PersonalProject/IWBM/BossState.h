#pragma once
#include "../D2DEngine/IFSMState.h"
#include "../D2DEngine/Vector2F.h"

class AnimationComponent;
class MovementComponent;

class BossMove:public IFSMState
{
	MovementComponent* movement;
	AnimationComponent* animation;
public:
	BossMove(MovementComponent* move,AnimationComponent* anim):movement(move),animation(anim){}
	virtual ~BossMove() {};
	virtual void Enter()override;
	virtual void Update(float dt)override;
	virtual void Exit()override;

	void TransformUpdate(float dt);
private:
	float _upY = 200;
	float _downY = 900;
	float _duration = 3.0; // 한 사이클의 기간 (초)
	float _time = 0.0; // 경과 시간
};

class BossDead:public IFSMState
{
	MovementComponent* movement;
	AnimationComponent* animation;
public:
	BossDead(MovementComponent* move,AnimationComponent* anim):movement(move),animation(anim){}
	virtual ~BossDead() {};
	virtual void Enter()override;
	virtual void Update(float dt)override;
	virtual void Exit()override;

private:

};

