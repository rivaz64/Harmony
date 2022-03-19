#pragma once

#include "ForDecHarmony.h"

namespace Harmony{

/**
 * @brief interface class for all the types of state machines
*/
class Controller
{
 public:
  
  Controller(const vector<State*>& states) :
    m_states(states){}

  /**
   * @brief changes this state machine to a new state
   * @param newState the state to where is changing
  */
  void
  ChangeToState(int newState);

  /**
   * @brief updates the state machine
  */
  void
  update();

  /**
   * @brief reacts to a recived message
   * @param msg 
  */
  virtual void
  onMessage(const Message& msg){}

  inline Pawn*
  getPawn(){
    return m_pawn;
  }
  
 protected:

  /**
   * @brief the state in which this machine is
  */
  State* m_actualState;

  /**
   * @brief all the states this machine can be in
  */
  vector<State*> m_states;

  /**
   * @brief the pawn that is being controlled
  */
  Pawn* m_pawn;


};

}


