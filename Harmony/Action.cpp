#include "Action.h"
#include "Controler.h"
#include "Debuger.h"

namespace Harmony{

void 
Action::execute(Controler* control)
{
#ifdef _DEBUG
  print("executing void action");
#endif
}

}

