#pragma once

class D2DRenderer;
class IScene;

class SceneGraph
{
protected:
	friend class IScene;
protected:
	IScene* m_currScenePtr;
	std::unordered_map<std::string, IScene*>m_sceneRegistry;
public:
	SceneGraph();
	~SceneGraph();

	IScene* GetCurrentScene();

	void ChangeScene(const std::string& sceneName);
	void Update(float dt);
	void Render(ID2D1HwndRenderTarget* pRenderTarget);
	virtual void RegisterScene(std::shared_ptr<D2DRenderer>winAppRenderer)=0;
};

class IScene
{
protected:
	friend class SceneGraph;
	std::unordered_map<std::string, IScene*>m_sceneDependencies;
	static SceneGraph* m_sceneManager;
	bool SceneEnd = false;
	//winApp Renderer ->text랑 이모저모들 사용하기위해 신도 들고있으려고? ...
	std::shared_ptr<D2DRenderer> pRenderer;

public:
	IScene(std::shared_ptr<D2DRenderer>winAppRenderer);
	virtual ~IScene();

	virtual void Update(float dt) = 0;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) = 0;
	virtual void InitScene() = 0;
	virtual void InitialGameObject() = 0;
	virtual void EndScene() = 0;

	void AddSceneDependency(IScene* scene, std::string sceneName);
};
