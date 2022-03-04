#include "StateMachine.h"

namespace Harmony{

void 
StateMachine::ChangeToState(int newState)
{
  m_actualState = m_states[newState];
}

}

