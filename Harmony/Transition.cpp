#include "Transition.h"
#include "Controller.h"
namespace Harmony{

void 
Transition::init(Controller* controller)
{
  m_delegate = Delegate<uint>::from_method<Controller,&Controller::ChangeToState>(controller);
}

void
Transition::execute()
{
  m_delegate(m_newState);
}

}

