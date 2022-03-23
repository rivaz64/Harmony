#pragma once
#include "Action.h"

namespace Harmony{

/**
 * @brief the pawn stayis in place and looks to an objective
*/
class LookTo :
  public Action
{
 public:
  void
  update(Controller* controller,float delta) override;

  float rotateRate;
};

}


