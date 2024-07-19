#include "pch.h"
#include "FSM.h"
#include "IFSMState.h"
#include "AnimationAsset.h"

FSM::FSM(GameObject* owner)
	:Component(owner,"FSM"), m_currentState(nullptr)
{
}

void FSM::AddState(const std::string& name, IFSMState* state)
{
	state->SetOwner(this);
	m_states[name] = state;
}

void FSM::SetState(const std::string& name)
{
	if (m_currentState)
	{
		m_currentState->Exit();
	}
	m_currentState = m_states[name];
	
	m_currentState->Enter();
}

void FSM::Update(float dt)
{
	if (m_currentState)
	{
		m_currentState->Update(dt);
	}
}
