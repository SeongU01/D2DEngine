#pragma once
#include "../D2DEngine/GameObject.h"
class AnimationComponent;
class ColliderComponent;
class MovementComponent;
class Camera;
class FSM;

class Boss : public GameObject
{
private:
	AnimationComponent* bossAnim;
	ColliderComponent* collider;
	MovementComponent* movement;
	FSM* fsm;
	
public:
	Boss(std::shared_ptr<Camera>camera);
	virtual ~Boss();

	virtual void Update(float dt)override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget)override;

	void Damaged();
	float GetHp()const { return _HP; }
	D2D1_RECT_F GetHpBar() const { return _HpBar; }
	ColliderComponent* GetCollider() { return collider; }
private:
	bool isDead = false;
	D2D1_RECT_F _HpBar;
	float _HP = 400;
	void SubscribeToEvents();
};

