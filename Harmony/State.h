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

  void
  onMessage(Controler* control,uint msg);

 private:

  /**
   * @brief the mapping of how the agent is going to react acording to a message
  */
  map<uint,vector<Action*>> m_reactions;

  /**
   * @brief 
  */
  //vector<Timer> m_timers;

  friend class Manager;
  friend class Controler;
};

}


