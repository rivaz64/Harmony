#include "Controller.h"
#include "State.h"

namespace Harmony{

Controller::Controller(const vector<State*>& states,
             const vector<TransitionDesciption>& defaultReactions,
             const vector<TransitionDesciption>& specificReactions) :
  m_states(states)                                  
{
  m_actualState = states[0];

  map<uint,Transition> defaults;

  for(auto& desc : defaultReactions){
    defaults.insert({desc.message,Transition(this,desc.toState)});
  }

  for(auto& state: states){
    state->m_reactions = defaults;
  }

  for(TransitionDesciption desc : specificReactions){
    m_states[desc.fromState]->m_reactions[desc.message] = Transition(this,desc.toState);
  }


}

void
Controller::ChangeToState(uint newState)
{
  m_actualState->onExit(this);
  m_actualState = m_states[newState];
  m_actualState->onEnter(this);
}

void 
Controller::update(float delta)
{
  m_actualState->update(this,delta);
}

void 
Controller::message(uint msg)
{
  m_actualState->onMessage(msg);
}


}

