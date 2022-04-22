#include "Controller.h"
#include "State.h"
#include "Detector.h"
#include "Transition.h"
#include "Pawn.h"

namespace Harmony{

Controller::Controller(const map<uint,State*>& states) :
  m_states(states)                                  
{
  m_actualState = states.begin()->second;
}

Controller::~Controller()
{
  size_t numStates = m_states.size();
  for(size_t i=0;i<numStates;++i){
    delete m_states[i];
  }
}

void 
Controller::init(vector<delegatorDesciption> defaultReactions, 
                 vector<delegatorDesciption> specificReactions)
{
  map<uint,Delegator*> defaults;

  for(auto& desc : defaultReactions){
    defaults.insert({desc.message,desc.toState});
  }

  for(auto& state: m_states){
    state.second->m_reactions = defaults;
  }

  for(auto& desc : specificReactions){
    m_states[desc.fromState]->m_reactions[desc.message] = desc.toState;
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
  for(auto& sence : m_activeSences){
    sence.second->update(delta);
  }
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

void 
Controller::newRandomPointToGo()
{
  auto location = m_pawn->getPosition();
  auto direction = m_pawn->getDirection();
  auto newPoint = location+direction*m_wanderDelta;
  auto wanderPoint = reachablePointInRadius(newPoint,m_wanderRadius);
  m_memory.addVariableOfType<Dimencion>("pointToGo");
  m_memory.setVariableAs<Dimencion>("pointToGo",wanderPoint);
}

void
Controller::goToPoint(const Dimencion& point)
{
  print("goToPoint does nothing");
}

Dimencion 
Controller::reachablePointInRadius(const Dimencion& point, float radius)
{
  print("reachablePointInRadius nothing");
  return Dimencion();
}

}
