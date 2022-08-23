#include "Transition.h"
#include "Controler.h"
namespace Harmony{

void 
Transition::execute(Controler* control)
{
  control->changeToState(m_newState);
}

}

