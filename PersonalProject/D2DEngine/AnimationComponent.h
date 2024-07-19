#pragma once
#include "RenderComponent.h"
class GameObject;
class AnimationAsset;
class AnimationInfo;
class FSM;
class IFSMState;

class AnimationComponent : public RenderComponent
{
public:
	AnimationComponent(GameObject* pOjbect, Camera* pCamera=nullptr);
	virtual ~AnimationComponent();
public:

	void SetAnimation(std::string status, bool mirror);
	void LoadAnimationAsset(const std::wstring strFilePath);
	void LoadAnimationInfo(const std::wstring txtPath);

	void SetAnimationEndAfterLastFrame(bool end);
	
	virtual void Update(float dt)override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget)override;

public:
	// �����ϴ� �ִϸ��̼� ����	
	AnimationAsset* m_pAnimationAsset;  // �����ϴ� �ִϸ��̼� ����
	ID2D1Bitmap* m_pBitmap;
	// �ν��Ͻ����� �ٸ� �ִϸ��̼� ����
	AnimationInfo* m_pAnimationInfo;	// ���� �ִϸ��̼� ������ ����
	AnimationInfo* m_pNextAnimationInfo = nullptr;	// ���� �ִϸ��̼� ������ ����
	std::wstring m_strAnimationAssetFilePath;    // �ִϸ��̼� ���� ���� �̸�
	float m_frameTime = 0.0f;	// ������ ����ð�
	int m_frameIndexCurr = 0;		// ���� ������ �ε���
	int m_frameIndexPrev = -1;		// ���� ������ �ε���
	int m_animationIndex = -1;	// ���� �ִϸ��̼� �ε���
	D2D1_RECT_F m_SrcRect;		// D2D1Bitmap�� Source ����
	D2D1_RECT_F m_DstRect;		// RenderTarget�� Destination ����		
	bool m_bMirror;				// �¿� ���� ����
	D2D1_MATRIX_3X2_F	m_imageTransform;	// �ݴ� �������� ������ ���� ��� Scale.x = -1.0f 

	bool m_bChangeStateAfterLastFrame;
	bool m_onAnimationEnd;

};