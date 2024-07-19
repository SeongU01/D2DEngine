#pragma once
class Component;
class Transform;
class Camera;
class FSM;
class IFSMState;

class GameObject
{
public:
	GameObject(std::shared_ptr<Camera> camera = nullptr);
	virtual ~GameObject();
	

protected:
	std::vector<Component*>m_ownComponents;
	std::vector<GameObject*>m_childObject;
	GameObject* m_pParentObject=nullptr;

public:
	virtual void Update(float dt);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

	Transform* transform;
	//Camera* pCamera;
	std::shared_ptr<Camera> pCamera;

public:
	Component* AddComponent(Component* pComponent);
	Component* GetComponent(const std::string& compName);


	void SetParent(GameObject* pParentObject)
	{ 
		m_pParentObject = pParentObject; 
		m_pParentObject->m_childObject.push_back(this);
	}
	GameObject* GetParent() { return m_pParentObject; }
	
};