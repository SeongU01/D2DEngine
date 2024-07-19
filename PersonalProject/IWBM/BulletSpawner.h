#pragma once
#include "../D2DEngine/GameObject.h"

class ColliderComponent;
class Bullet;
class IScene;
class Boss;

class BulletSpawner : public GameObject
{
private:
	ColliderComponent* collider;
public:
	BulletSpawner(GameObject* pParent);
	virtual ~BulletSpawner();
	virtual void Update(float dt)override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget)override;

	std::list<Bullet*> bullets;
	ColliderComponent* GetCollider() { return collider; }

	void BulletUpdate();
	void BulletFire(float dt);
	void ColliderUpdate();
	void DirectionUpdate();

	void SetBulletColiiderInteration(ColliderComponent* _collider);
	void TriggerBossDamaged();

	//콜라이더
	std::vector<ColliderComponent*>currSceneObjectCollider;
	ColliderComponent* bossCol;
public:
	enum Direction { LEFT, RIGHT };
	float fireDelay;
	//default 방향 right
	Direction currentDirection=RIGHT;
};

