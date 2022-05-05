#pragma once

#include "Prerequisites.h"
#include "Transition.h"

namespace Harmony{

/**
 * @brief a state for the state machine
*/
class State
{
 public:

  virtual void
  onMessage(uint msg);

 private:

  /**
   * @brief the mapping of how the agent is going to react acording to a message
  */
  map<uint,Delegator*> m_reactions;

  friend class Manager;
  friend class Controller;
};

}


