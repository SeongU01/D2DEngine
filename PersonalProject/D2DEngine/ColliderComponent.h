#pragma once
#include "Component.h"
#include "Vector2F.h"
#include "AABB.h"
class GameObject;

class ColliderComponent : public Component 
{
public:
	ColliderComponent(GameObject* pObject);
	virtual ~ColliderComponent() { delete m_colliderAABB; }
public:
	virtual void Update(float dt)override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget)override;

	void SetColliderRect(D2D_RECT_F rect);
	void UpdateCollider(D2D_RECT_F rect);
	void AddCheckColliderList(AABB* aabb,std::string objectName);

	D2D_RECT_F GetColliderRect() const { return m_colliderRect; }
	D2D_RECT_F GetColideWithRect()const { return m_colideWithRect; }
	std::string GetColideWith() const { return m_colideWith; }
	AABB* GetCollider()const { return m_colliderAABB; }
	bool IsCollide() { return m_onCollider; }
	std::pair<CollisionDirection, CollisionDirection> GetCollisionDetails() { return collisionDetails; }
	//first=this, second=other
private:
	bool m_onCollider;
	std::vector<std::pair<AABB*,std::string>> m_checkColliders;
	D2D_RECT_F m_colliderRect;
	D2D_RECT_F m_colideWithRect;
	std::pair<CollisionDirection, CollisionDirection> collisionDetails;
	AABB* m_colliderAABB;
	std::string m_colideWith;
};

