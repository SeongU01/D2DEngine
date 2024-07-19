#pragma once
#include "RenderComponent.h"
#include "unordered_map"
#include <string>
class GameObject;

class TextureComponent :public RenderComponent
{
public:
	//짤려져있는 이미지 사용함
	//상태에 따른 애니메이션 상태->std::string
	std::unordered_map < std::string, std::vector<ID2D1Bitmap*>>m_animations;
	ID2D1Bitmap* m_currBitmap;
	

public:
	TextureComponent(GameObject* pObject);
	~TextureComponent() {}

	virtual void Update(float dt)override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget)override;

	bool SetAnimation(std::string status,const std::wstring& szFilePath);
};
