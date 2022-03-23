#pragma once
#include "State.h"

namespace Harmony{

/**
 * @brief actions are things the pawn can make
*/
class Action
{
 public:
  virtual void
  update(Controller* controller,float delta){}
};

}


