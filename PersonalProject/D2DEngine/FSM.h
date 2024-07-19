#pragma once
#include "Component.h"

class IFSMState;
class AnimationComponent;
class MovementComponent;
class GameObject;

class FSM :public Component
{
private:
	std::unordered_map<std::string, IFSMState*>m_states;
	IFSMState* m_currentState;
public:
	FSM(GameObject* owner);
	~FSM()
	{
		for (auto &iter : m_states)
		{
			delete iter.second;
		}
	}

	void AddState(const std::string& name, IFSMState* state);
	
	void SetState(const std::string& name);

	virtual void Update(float dt)override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget)override {};
};

