#pragma once
#include "../D2DEngine/SceneGraph.h"

class SceneManager :public SceneGraph
{
public:
	virtual void RegisterScene(std::shared_ptr<D2DRenderer>winAppRenderer)override;
};