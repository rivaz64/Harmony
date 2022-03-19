#pragma once
#include "State.h"

namespace Harmony{

class GoToPoint :
  public State
{
  public:
  void
  onUpdate(Controller* controller) override;
};

}


