#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Vector2F.h"

class AnimationComponent;
class ColliderComponent;
class MovementComponent;
class Camera;

class Player :public GameObject
{
private:
	AnimationComponent* playerAnim;
	ColliderComponent* collider;
	MovementComponent* movement;
	enum Direction { LEFT, RIGHT ,UP,DOWN};
	Direction jumpDirection;
	Direction currentDirection;
	FSM* fsm;
public:
	Player(std::shared_ptr<Camera> camera=nullptr);
	virtual ~Player();
	
	virtual void Update(float dt)override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget)override;

	void TransformUpdate(float dt);
	void DoJump(float dt);
	AnimationComponent* GetAnimation() { return playerAnim; }
	ColliderComponent* GetCollider() { return collider; }
	void Gravity(float dt);
private:
	
	bool isJumping;
	bool onGravity;
	float gravity;
	int jumpCount;
	float jumpVelocity;
	float downVelocity;

	Vector2F moveVelocity;
};