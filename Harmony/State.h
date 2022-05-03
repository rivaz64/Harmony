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

  /**
   * @brief function executed while in this state
   * @param  
  */
  virtual void
  update(Controller*,float delta){}

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


