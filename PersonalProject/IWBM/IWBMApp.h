#pragma once
#include "../D2DEngine/WinGameApp.h"
#include "Resource.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/BitmapComponent.h"
#include "../D2DEngine/TransformComponent.h"
#include "../D2DEngine/AnimationComponent.h"
#include "../D2DEngine/TextComponent.h"

class IWBMApp : public WinGameApp
{
private:
	class SceneManager* _SceneGraph;

public:
	IWBMApp(HINSTANCE hInstance);
	~IWBMApp();

	virtual bool Initialize(UINT width, UINT height) override;
	virtual void Update(float fTimeElapsed) override;
	virtual void Render() override;
	virtual void Uninitialize()override;

};

