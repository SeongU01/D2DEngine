#include "pch.h"
#include "SceneManager.h"
//scene
#include "Stage1.h"

void SceneManager::RegisterScene(std::shared_ptr<D2DRenderer>winAppRenderer)
{
	m_sceneRegistry["Entry"] = new Stage1(winAppRenderer);
	
	m_currScenePtr = m_sceneRegistry.find("Entry")->second;
	m_currScenePtr->InitScene();
}
