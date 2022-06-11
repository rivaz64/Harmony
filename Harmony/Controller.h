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
  OnSeen,
  OnObstacle,
  OnDie
};
}

namespace STATES{
enum E
{
  None,
  Wander,
  Pursue,
  Attack,
  Evade,
  Dead
};
}

namespace MEMENTOS{
enum E
{
  Obstacle,
  Pawn
};
}

struct DelegatorDesciption{
  STATES::E fromState;
  MESSAGES::E message;
  vector<Delegator*> toState;
};

struct Memento{
  /**
   * @brief the time left before forgeting
  */
  float timeLeft;

  /**
   * @brief how to react if remembering this
  */
  MESSAGES::E msg;
};

template<class T>
struct Memory: 
  Memento
{
  /**
   * @brief the thing that is being remember
  */
  T memory;
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
   * @brief remembers something for a certain time
   * @param memory 
  */
  void
  remember(MEMENTOS::E type , Memento* memory);

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
  nextPointPath();

  /**
   * @brief goes to the next point when patrolling 
  */
  void 
  nextPointPatrol();

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

 protected:

  /**
   * @brief the state in which this machine is
  */
  STATES::E m_actualState;

  /**
   * @brief all the states this machine can be in
  */
  map<STATES::E,State*> m_states;

  /**
   * @brief the pawn that is being controlled
  */
  Pawn* m_pawn;

  /**
   * @brief what is remembered
  */
  map<MEMENTOS::E,list<Memento*>> m_memory;

  float m_wanderDelta = 36;
  float m_wanderRadius = 18;
  float deltaTime;

  friend class Manager;
};

}


