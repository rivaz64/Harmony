#pragma once
#include "Transition.h"
#include "Manager.h"
#include "flags.h"
namespace Harmony{

class Wander :
  public Transition
{
  Wander() :
    Transition((uint)STATES::GoToPoint){}

  void
  execute() override;
};

}


