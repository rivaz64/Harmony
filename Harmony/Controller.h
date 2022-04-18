#pragma once

#include "Prerequisites.h"
#include "BlackBoard.h"
#include "Delegate.h"

namespace Harmony{

enum class Messages
{
  OnFinish
};

struct delegatorDesciption{
  uint fromState;
  uint message;
  Delegator toState;
};

/**
 * @brief a state machine that controlls a pawn
*/
class Controller
{
 public:
  
  Controller(const vector<State*>& states);

  void
  init(vector<delegatorDesciption> defaultReactions,
       vector<delegatorDesciption> specificReactions);

  /**
   * @brief changes this state machine to a new state
   * @param newState the state to where is changing
  */
  void
  ChangeToState(uint newState);

  /**
   * @brief updates the state machine
  */
  void
  update(float delta);

  /**
   * @brief reacts to a recived message
   * @param msg 
  */
  void
  message(uint msg);

  /**
   * @brief gives a new sence to this controller
   * @param id 
   * @param sence 
  */
  void
  addDetector(uint id,Detector* sence);

  /**
   * @brief stops detecting with this sence
   * @param id 
   * @param sence 
  */
  void
  deactiveSence(uint id);

  /**
   * @brief starts detecting with this sence
   * @param id 
   * @param sence 
  */
  void
  activeSence(uint id);

  inline Pawn*
  getPawn(){
    return m_pawn;
  }

  inline void
  setPawn(Pawn* pawn){
    m_pawn = pawn;
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
   * @brief all the ways the controller can feel the world
  */
  map<uint,Detector*> m_sences;

  /**
   * @brief this are the ways the actor is activly feeling the world
  */
  map<uint,Detector*> m_activeSences;

  /**
   * @brief the pawn that is being controlled
  */
  Pawn* m_pawn;

  friend class Manager;
};

}


