#pragma once
#include "Prerequisites.h"
#include "Controller.h"

namespace Harmony{

class AIController :
  public Controller
{
 public:
  
  AIController(const vector<State*>& states):
    Controller(states){}

  /**
   * @brief chooses a new random location to go if the controller does not have a location to go
  */
  void
  newRandomPointToGo();

 protected:

  float m_wanderDelta = 36;
  float m_wanderRadius = 18;
};

}

