#include "State.h"

namespace Harmony{

void 
State::onUpdate(Controller* controller, float delta)
{
  m_action->update(controller,delta);
}

}

