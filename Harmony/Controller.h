#pragma once

#include "Prerequisites.h"
#include "BlackBoard.h"
#include "Delegate.h"

namespace Harmony{

namespace MESSAGES{
enum E
{
  OnUpdate,
  OnEnter,
  OnExit,
  OnFinish,
  OnSeen
};
}

namespace STATES{
enum E
{
  Wander,
  Pursue,
  Attack
};
}


struct DelegatorDesciption{
  STATES::E fromState;
  MESSAGES::E message;
  vector<Delegator*> toState;
};

struct Memory{

  /**
   * @brief the time left before forgeting
  */
  float timeLeft;

  /**
   * @brief the message to be executing
  */
  vector<MESSAGES::E> msg;
};

/**
 * @brief a state machine that controlls a pawn
*/
class Controller
{
 public:
  
  Controller(const map<STATES::E,State*>& states);

  virtual 
  ~Controller();

  void
  init(vector<DelegatorDesciption> defaultReactions,
       vector<DelegatorDesciption> specificReactions);

  /**
   * @brief changes this state machine to a new state
   * @param newState the state to where is changing
  */
  void
  ChangeToState(STATES::E newState);

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
  message(MESSAGES::E msg);

  /**
   * @brief chooses a new random location to go if the controller does not have a location to go
  */
  void
  newRandomPointToGo();

  /**
   * @brief separates from the others to not collide
  */
  void
  separate();

  /**
   * @brief aligns his direction whit the ones it sees
  */
  void
  align();

  /**
   * @brief makes the pawn stay in a group
  */
  void
  coher();

  /**
   * @brief goes to the point goToPoint
  */
  void
  goToPoint();

  /**
   * @brief looks to the point goToPoint
  */
  void
  lookTo();

  /**
   * @brief ends the action after a certain time
  */
  void
  wait();

  /**
   * @brief sets the timer to 0
  */
  void
  restart();

  /**
   * @brief goes to the next point when following a path
  */
  void 
  nextPoint();

  /**
   * @brief goes to a point using the system the controller has
   * @param point 
  */
  virtual void
  goToPoint(const Dimencion& point);

  /**
   * @brief gets a random point that can be reached from a certain radius
   * @param point 
   * @param radius 
  */
  virtual Dimencion
  reachablePointInRadius(const Dimencion& point, float radius);

  /**
   * @brief to recive a mesage and do not react
  */
  void
  nothing(){}

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
   * @brief the variables of this controller
  */
  BlackBoard m_variables;

  /**
   * @brief what is remembered
  */
  list<Memory> m_memory;

 protected:

  /**
   * @brief the state in which this machine is
  */
  State* m_actualState;

  /**
   * @brief all the states this machine can be in
  */
  map<STATES::E,State*> m_states;

  /**
   * @brief the pawn that is being controlled
  */
  Pawn* m_pawn;

  float m_wanderDelta = 36;
  float m_wanderRadius = 18;
  float deltaTime;

  friend class Manager;
};

}


