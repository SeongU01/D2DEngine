#include "pch.h"
#include "SceneGraph.h"
SceneGraph* IScene::m_sceneManager = nullptr;
SceneGraph::SceneGraph()
{
	IScene::m_sceneManager = this;
}

SceneGraph::~SceneGraph()
{
	for (auto it = m_sceneRegistry.begin(); it != m_sceneRegistry.end(); ++it)
	{
		delete it->second;
	}
}

IScene* SceneGraph::GetCurrentScene()
{
	return m_currScenePtr;
}

void SceneGraph::ChangeScene(const std::string& sceneName)
{
	IScene* newScene = m_currScenePtr->m_sceneDependencies.find(sceneName)->second;
	m_currScenePtr->EndScene();
	m_currScenePtr = newScene;
	m_currScenePtr->InitScene();
}

void SceneGraph::Update(float dt)
{
	m_currScenePtr->Update(dt);
}

void SceneGraph::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	m_currScenePtr->Render(pRenderTarget);
}

//���� �̴��Ҷ� �� ���� �߰����ֱ�



IScene::IScene(std::shared_ptr<D2DRenderer> winAppRenderer)
	:pRenderer(winAppRenderer)
{
}

IScene::~IScene()
{
}

void IScene::AddSceneDependency(IScene* scene, std::string sceneName)
{
	m_sceneDependencies[sceneName] = scene;
}
