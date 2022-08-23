#pragma once

#include "Prerequisites.h"
#include "Action.h"
#include "Controler.h"

namespace Harmony{

/**
 * @brief a way to change states 
*/
class Transition:
  public Action
{
 public:

  /**
   * @brief changes to the new state
  */
  void
  execute(Controler* control) override;

 protected:
  
  Transition() = default;

  /**
   * @brief the new state to go to
  */
  STATES::E m_newState;
};

}


