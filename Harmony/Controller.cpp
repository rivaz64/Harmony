#include "Controller.h"
#include "State.h"

namespace Harmony{

void 
Controller::ChangeToState(int newState)
{
  m_actualState->onExit(this);
  m_actualState = m_states[newState];
  m_actualState->onEnter(this);
}

void 
Controller::update(float delta)
{
  m_actualState->onUpdate(this,delta);
}

}

