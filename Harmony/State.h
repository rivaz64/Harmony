#pragma once

#include "ForDecHarmony.h"

namespace Harmony{

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
  onUpdate(Controller*){}


};

}


