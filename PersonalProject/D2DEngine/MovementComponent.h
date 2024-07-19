#pragma once
#include "Component.h"
#include "Vector2F.h"

class GameObject;
class Transform;

class MovementComponent :public Component
{
public:
	enum Direction { LEFT, RIGHT, UP, DOWN };
public:
	MovementComponent(GameObject* pObject);
	virtual ~MovementComponent();

public:
	virtual void Update(float dt)override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget)override {};
	void SetSpeed(float speed) { _speed = speed; }
	void SetDirection(const Vector2F& direction) { _direction = direction; }

private:
	Vector2F _direction;
	float _speed = 0.f;
};

