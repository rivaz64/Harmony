#pragma once

#include "Prerequisites.h"
#include "Delegate.h"
#include "Controller.h"

namespace Harmony{

/**
 * @brief a way to change states in a certain event
*/
class Transition:
  public Delegate<STATES::E>
{
 public:

  /**
   * @brief 
   * @param controller the controller that is using this transicion
   * @param newState the state that is going to be in
  */
  Transition(STATES::E newState, Controller* control) :
    Delegate<STATES::E>(*Delegate<STATES::E>::createPtr<Transition,Controller,&Controller::ChangeToState>(control)),
    m_newState(newState)
  {}

  /**
   * @brief changes to the new state
  */
  void
  execute() override;

 protected:
  
  Transition() = default;

  /**
   * @brief the new state to go to
  */
  STATES::E m_newState;

  friend class Delegate<STATES::E>;
};

}


