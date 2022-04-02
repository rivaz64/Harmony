#pragma once

#include "Prerequisites.h"
#include "Delegate.h"
#include "Controller.h"

namespace Harmony{

class Transition :
  public Delegate<uint>
{
 public:
  Transition() = default;

  Transition(Controller* controller,uint newState) :
    Delegate<uint>(Delegate<uint>::from_method<Controller,&Controller::ChangeToState>(controller)),
    m_newState(newState)
  {}

  void
  execute();

 private:
  
  uint m_newState;
};

}


