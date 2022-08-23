#include "State.h"
#include "Debuger.h"

namespace Harmony{

void State::onMessage(Controler* control,uint msg)
{
  #ifdef _DEBUG
  if(m_reactions.find(msg)==m_reactions.end()){
    print("unhandled message");
    print(msg);
    return;
  }
  #endif
  for(auto& reaction : m_reactions[msg]){
    reaction->execute(control);
  }
}

}

