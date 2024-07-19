#pragma once
#include "FSM.h"

class MovementComponent;
class AnimationComponent;

class IFSMState
{
  FSM* pOwner;
public:
  IFSMState(){}
  virtual ~IFSMState() {}
  
  virtual void Enter() = 0;
  virtual void Update(float dt) = 0;
  virtual void Exit() = 0;

  void SetOwner(FSM* owner) { pOwner = owner; }
  FSM* GetOwner() { return pOwner; }
};

