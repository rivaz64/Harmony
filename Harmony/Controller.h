#pragma once

#include "ForDecHarmony.h"
#include "BlackBoard.h"

namespace Harmony{

/**
 * @brief a state machine that controlls a pawn
*/
class Controller
{
 public:
  
  Controller(const vector<State*>& states) :
    m_states(states)
  {
    m_actualState = states[0];
  }

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
  update(float delta);

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
  
 public:
  /**
   * @brief the things this controller remembers
  */
  BlackBoard m_memory;

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

  friend class Manager;
};

}


