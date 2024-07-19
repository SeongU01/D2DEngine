#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Vector2F.h"

class AnimationComponent;
class ColliderComponent;
class MovementComponent;

class Bullet : public GameObject
{
	enum Direction { LEFT, RIGHT };

private:
	AnimationComponent* bulletAnim;
	ColliderComponent* collider;
	MovementComponent* movement;

	Direction bulletDirection;
public:
	Bullet(int direction, std::shared_ptr<Camera> camera);
	virtual ~Bullet();

	virtual void Update(float dt)override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget)override;

	void TransformUpdate(float dt);

	AnimationComponent* GetAnimation() { return bulletAnim; }
	ColliderComponent* GetCollider() { return collider; }

private:
	float velocity;
};

