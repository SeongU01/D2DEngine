#pragma once

class GameObject;

class Component
{
protected:
	GameObject* m_pObject;
	std::string m_pName;
	
public:
	Component(GameObject* pObject, const std::string& name);
	
	virtual ~Component();
	
	const std::string& GetName()const { return m_pName; }
	void SetObject(GameObject* pObject) { m_pObject = pObject; }
	GameObject* GetOwner() { return m_pObject; }
public:
	virtual void Update(float dt)=0;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) = 0;
	
};

