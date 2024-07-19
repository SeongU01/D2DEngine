#include "pch.h"
#include "Camera.h"
#include "GameObject.h"
#include "WinGameApp.h"
#include "Transform.h"

#include "DebugConsole.h"

#include "ColliderComponent.h"
#include "MovementComponent.h"
#include "RenderComponent.h"

Camera::Camera(D2D_SIZE_U clientSize)
	: clientSize(clientSize)
{
	m_matCameraInv = D2D1::Matrix3x2F::Identity();
	m_cameraCollider = new ColliderComponent(this);
	m_cameraMovement = new MovementComponent(this);
}

void Camera::Update(float dt)
{
	m_cameraCollider->SetColliderRect(
		D2D_RECT_F{
			transform->GetLocation().x,
			transform->GetLocation().y,
			transform->GetLocation().x+clientSize.width ,
			transform->GetLocation().y+clientSize.height
		}
	);
	__super::Update(dt);
	D2D1InvertMatrix(&transform->m_worldTransform);
}


void Camera::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
}