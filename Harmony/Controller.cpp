#include "Controller.h"
#include "State.h"
#include "Detector.h"

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

void 
Controller::addDetector(uint id, Detector* sence)
{
  m_sences.insert({id,sence});
  m_activeSences.insert({id,sence});
  sence->m_controller = this;
}

void
Controller::deactiveSence(uint id)
{
  if(m_activeSences.find(id) != m_activeSences.end()){
    m_activeSences.erase(id);
  }
  #ifdef _DEBUG
  else{
    print("trying to deactivate something not active");
    print(id);
  }
  #endif
}

void 
Controller::activeSence(uint id)
{
  if(m_sences.find(id) != m_sences.end() || m_activeSences.find(id) == m_activeSences.end()){
    m_activeSences.insert({id,m_sences[id]});
  }
  #ifdef _DEBUG
  else{
    print("trying to activate something allready active or unkown");
    print(id);
  }
  #endif
}


}

