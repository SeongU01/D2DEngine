#include "pch.h"
#include "GameObject.h"
#include "AnimationComponent.h"
#include "ResourceManager.h"
#include "AnimationAsset.h"
#include "FSM.h"
#include "Camera.h"
AnimationComponent::AnimationComponent(GameObject* pObject, Camera* pCamera)
  : RenderComponent(pObject, pCamera), m_pAnimationAsset(nullptr), m_pAnimationInfo(new AnimationInfo)
{
}

AnimationComponent::~AnimationComponent()
{
  if (m_pAnimationInfo)
  {
    delete m_pAnimationInfo;
    m_pAnimationInfo = nullptr;
  }
  ResourceManager::Get().ReleaseAnimAsset(m_strAnimationAssetFilePath);
}

void AnimationComponent::SetAnimation(std::string status, bool mirror)
{
  if (m_pAnimationAsset == nullptr)
  {
    throw std::runtime_error("AnimationComponent::SetAnimation - m_pAnimationAsset is nullptr");
  }

  AnimationInfo* pFound = m_pAnimationAsset->GetAnimationInfo(status);

  if (pFound == nullptr)
  {
    throw std::runtime_error("AnimationComponent::SetAnimation - AnimationInfo not found");
  }

  // 이전 m_pAnimationInfo 메모리 해제
  if (m_pAnimationInfo)
  {
    delete m_pAnimationInfo;
  }

  // m_pAnimationInfo 업데이트
  m_pAnimationInfo = new AnimationInfo(*pFound);
  m_bMirror = mirror;
  m_frameIndexCurr = 0;
  m_frameIndexPrev = 0;
  m_frameTime = 0.f;
}

void AnimationComponent::LoadAnimationAsset(const std::wstring strFilePath)
{
  m_pBitmap = ResourceManager::Get().GetImage(strFilePath);
}

void AnimationComponent::LoadAnimationInfo(const std::wstring txtPath)
{
  m_strAnimationAssetFilePath = txtPath;
  ResourceManager::Get().CreateAnimAsset(txtPath, &m_pAnimationAsset);
}


void AnimationComponent::SetAnimationEndAfterLastFrame(bool end)
{
  m_onAnimationEnd = end;
}

void AnimationComponent::Update(float dt)
{
  __super::Update(dt);

  if (m_pAnimationAsset == nullptr)
  {
    throw std::runtime_error("AnimationComponent::Update - m_pAnimationAsset is nullptr");
  }

  if (m_pAnimationInfo == nullptr)
  {
    return;
  }

  m_frameTime += dt;
  int MaxFrameCount = static_cast<int>(m_pAnimationInfo->frames.size());
  if (m_frameTime >= m_pAnimationInfo->frames[m_frameIndexCurr].duration)
  {
    m_frameIndexCurr++;
    if (m_frameIndexCurr == MaxFrameCount)
    {
      if (m_pAnimationInfo->Loop)
        m_frameIndexCurr -= MaxFrameCount;
      //STATE 다음 anim으로 변경. fsm state에서 설정
      //ex)animComp->m_pAnimationInfo->SetNextAnimInfo("Idle");
      /*else
      {
        m_pObject->m_FSM->SetState(m_pAnimationInfo->nextAnim, this, m_bMirror);
      }*/
      else
      {
        SetAnimationEndAfterLastFrame(true);
        return;
        //m_frameIndexCurr -= MaxFrameCount;
        //SetAnimation(m_pAnimationInfo->nextAnim, m_bMirror);
      }
    }
    m_frameTime -= m_pAnimationInfo->frames[m_frameIndexCurr].duration;
  }

  const FrameInfo& Frame = m_pAnimationInfo->frames[m_frameIndexCurr];

  m_SrcRect = Frame.source;
  m_DstRect = { 0,0,m_SrcRect.right - m_SrcRect.left,m_SrcRect.bottom - m_SrcRect.top };
  m_center.x = Frame.center.x;
  m_center.y = Frame.center.y;

  if (m_bMirror)
  {
    m_imageTransform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(m_center.x, 0));
    //transform->SetScale(-1.f, 1.f);
  }
  else
  {
    m_imageTransform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(0, 0));
    //transform->SetScale(1.f, 1.f);
  }
}

void AnimationComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
  if (m_pAnimationInfo == nullptr)
  {
    throw std::runtime_error("AnimationComponent::Render - m_pAnimationInfo is nullptr");
  }
  __super::Render(pRenderTarget);
  transform->m_worldTransform = m_imageTransform * transform->m_worldTransform;
  pRenderTarget->SetTransform(transform->m_worldTransform);
  pRenderTarget->DrawBitmap(m_pBitmap, m_DstRect, 1.f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect);
}

