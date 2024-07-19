#pragma once
#include "RenderComponent.h"
#include "unordered_map"
#include <string>
class GameObject;

class TextureComponent :public RenderComponent
{
public:
	//©�����ִ� �̹��� �����
	//���¿� ���� �ִϸ��̼� ����->std::string
	std::unordered_map < std::string, std::vector<ID2D1Bitmap*>>m_animations;
	ID2D1Bitmap* m_currBitmap;
	

public:
	TextureComponent(GameObject* pObject);
	~TextureComponent() {}

	virtual void Update(float dt)override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget)override;

	bool SetAnimation(std::string status,const std::wstring& szFilePath);
};
