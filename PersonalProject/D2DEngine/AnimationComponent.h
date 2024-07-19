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
	// 공유하는 애니메이션 정보	
	AnimationAsset* m_pAnimationAsset;  // 공유하는 애니메이션 정보
	ID2D1Bitmap* m_pBitmap;
	// 인스턴스마다 다른 애니메이션 정보
	AnimationInfo* m_pAnimationInfo;	// 현재 애니메이션 프레임 정보
	AnimationInfo* m_pNextAnimationInfo = nullptr;	// 다음 애니메이션 프레임 정보
	std::wstring m_strAnimationAssetFilePath;    // 애니메이션 정보 파일 이름
	float m_frameTime = 0.0f;	// 프레임 진행시간
	int m_frameIndexCurr = 0;		// 현재 프레임 인덱스
	int m_frameIndexPrev = -1;		// 이전 프레임 인덱스
	int m_animationIndex = -1;	// 현재 애니메이션 인덱스
	D2D1_RECT_F m_SrcRect;		// D2D1Bitmap의 Source 영역
	D2D1_RECT_F m_DstRect;		// RenderTarget의 Destination 영역		
	bool m_bMirror;				// 좌우 반전 여부
	D2D1_MATRIX_3X2_F	m_imageTransform;	// 반대 방향으로 뒤집기 위한 행렬 Scale.x = -1.0f 

	bool m_bChangeStateAfterLastFrame;
	bool m_onAnimationEnd;

};