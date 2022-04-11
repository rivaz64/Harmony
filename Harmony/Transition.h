#pragma once

#include "Prerequisites.h"
#include "Delegate.h"

namespace Harmony{

/**
 * @brief a way to change states in a certain event
*/
class Transition
{
 public:
  Transition() = default;

  /**
   * @brief 
   * @param controller the controller that is using this transicion
   * @param newState the state that is going to be in
  */
  Transition(uint newState) :
    m_newState(newState)
  {}

  /**
   * @brief inits this execution to a specific controller
   * @param controller 
  */
  void
  init(Controller* controller);

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

  /**
   * @brief the one in charge of changing the state
  */
  Delegate<uint> m_delegate;
};

}


