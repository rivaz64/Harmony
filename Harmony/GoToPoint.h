#pragma once
#include "Action.h"

namespace Harmony{

/**
 * @brief action of go to a point directly
*/
class GoToPoint :
  public Action
{
  public:

  void
  update(Controller* controller,float delta) override;

  /**
   * @brief the radius at wich it has arrived
  */
  float aceptanceRadius;
};

}


