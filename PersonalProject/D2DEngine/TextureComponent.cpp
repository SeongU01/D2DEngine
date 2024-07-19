#include "pch.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "ResourceManager.h"

TextureComponent::TextureComponent(GameObject* pObject)
	:RenderComponent(pObject)
{

}

void TextureComponent::Update(float dt)
{
}

void TextureComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	RenderComponent::Render(pRenderTarget);

	pRenderTarget->DrawBitmap(m_currBitmap);
}


//���� �̸��� �ִϸ��̼� ������� 1 2 3 4 5 6...���� �����ؾ���.
bool TextureComponent::SetAnimation(const std::string status, const std::wstring& szFilePath)
{
	std::vector<ID2D1Bitmap*>animsVector;
	int n = 1;
	std::wstring newPath = szFilePath;
	newPath = newPath + std::to_wstring(n);
	while (ResourceManager::Get().GetImage(newPath)!=nullptr)
	{
		animsVector.push_back(ResourceManager::Get().GetImage(newPath));
		n++;
	}
	m_animations[status] = animsVector;
	return true;
}
