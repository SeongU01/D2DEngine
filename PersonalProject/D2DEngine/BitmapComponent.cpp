#include "pch.h"
#include "GameObject.h"
#include "BitmapComponent.h"
#include "ResourceManager.h"
#include "Camera.h"

BitmapComponent::BitmapComponent(GameObject* pObject, Camera* pCamera)
  :RenderComponent(pObject,pCamera), m_pBitmap(nullptr)
{
}

bool BitmapComponent::SetImage(const std::wstring& strFilePath)
{
  m_pBitmap = ResourceManager::Get().GetImage(strFilePath);
  m_center = { m_pBitmap->GetSize().width / 2,m_pBitmap->GetSize().height / 2 };
  return true;
}

void BitmapComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
  __super::Render(pRenderTarget);
  pRenderTarget->SetTransform(transform->m_worldTransform);
  pRenderTarget->DrawBitmap(m_pBitmap);
  
}
