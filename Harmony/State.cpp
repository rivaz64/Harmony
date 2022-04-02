#include "State.h"


namespace Harmony{

void 
State::onMessage(uint msg)
{
  m_reactions[msg].execute();
}

}

