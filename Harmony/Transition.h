#pragma once

#include "Prerequisites.h"
#include "Delegate.h"
#include "Controller.h"

namespace Harmony{

/**
 * @brief a way to change states in a certain event
*/
class Transition :
  public Delegate<uint>
{
 public:
  Transition() = default;

  /**
   * @brief 
   * @param controller the controller that is using this transicion
   * @param newState the state that is going to be in
  */
  Transition(Controller* controller,uint newState) :
    Delegate<uint>(Delegate<uint>::from_method<Controller,&Controller::ChangeToState>(controller)),
    m_newState(newState)
  {}

  /**
   * @brief changes to the new state
  */
  void
  execute();

 protected:
  
  /**
   * @brief the new state to go to
  */
  uint m_newState;
};

}


