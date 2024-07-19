#pragma once
#include "Vector2F.h"
#include "GameObject.h"
#include "AABB.h"

class MovementComponent;
class ColliderComponent;
class Camera : public GameObject
{
public:
	Camera(D2D_SIZE_U clientSize);
	virtual ~Camera() {};

	virtual void Update(float dt)override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget)override;
	D2D_SIZE_U clientSize;
	ColliderComponent* m_cameraCollider;
	MovementComponent* m_cameraMovement;

	D2D_MATRIX_3X2_F m_matCameraInv; // 카메라 좌표계 변환을 위한 행렬
};

