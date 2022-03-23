#pragma once

#include "Prerequisites.h"
#include "Action.h"

namespace Harmony{

/**
 * @brief a state for the state machine
*/
class State
{
 public:
  
  /**
   * @brief function executed when this state is entered
   * @param  
  */
  virtual void
  onEnter(Controller*){}

  /**
   * @brief function executed when this state is exited
   * @param  
  */
  virtual void
  onExit(Controller*){}

  /**
   * @brief function executed while in this state
   * @param  
  */
  virtual void
  onUpdate(Controller*,float delta);

 private:

  Action* m_action;

  friend class Manager;
};

}


