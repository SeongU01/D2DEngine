#pragma once=
#include "../D2DEngine/IFSMState.h"
#include "../D2DEngine/Vector2F.h"

class AnimationComponent;
class MovementComponent;

class Idle :public IFSMState
{
	MovementComponent* movement;
	AnimationComponent* animation;
public:
	Idle(MovementComponent* move,AnimationComponent* anim):movement(move), animation(anim){}
	virtual ~Idle() {};
	virtual void Enter()override;
	virtual void Update(float dt)override;
	virtual void Exit()override;
};


class Move :public IFSMState
{
	enum Direction { LEFT, RIGHT };
	Direction currentDirection;
	MovementComponent* movement;
	AnimationComponent* animation;
	Vector2F moveVelocity = { 250,0 };
public:
	Move(MovementComponent* move, AnimationComponent* anim) :movement(move), animation(anim) {}
	virtual ~Move() {};
	virtual void Enter()override;
	virtual void Update(float dt)override;
	virtual void Exit()override;

	void RightAnim(float dt);
	void LeftAnim(float dt);
};


class Jump :public IFSMState
{
	enum Direction { LEFT, RIGHT };
	Direction currentDirection;
	MovementComponent* movement;
	AnimationComponent* animation;
	//프레임의 개수
	int MaxFrameCount;
public:
	Jump(AnimationComponent* anim) : animation(anim) {}
	virtual ~Jump() {};

	virtual void Enter()override;
	virtual void Update(float dt)override;
	virtual void Exit()override;
};

class Attack :public IFSMState
{
	enum Direction { LEFT, RIGHT };
	Direction currentDirection;
	AnimationComponent* animation;
	//프레임의 개수
	int MaxFrameCount;
public:
	Attack(AnimationComponent* anim) : animation(anim) {}
	virtual ~Attack() {};

	virtual void Enter()override;
	virtual void Update(float dt)override;
	virtual void Exit()override;
};