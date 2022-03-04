#pragma once

#include "ForDecHarmony.h"

namespace Harmony{

/**
 * @brief interface class for all the types of state machines
*/
class StateMachine
{
 public:

  void
  ChangeToState(int newState);
  
 protected:

  /**
   * @brief the state in which this machine is
  */
  State* m_actualState;

  /**
   * @brief all the states this machine can be in
  */
  vector<State*> m_states;
};

}


