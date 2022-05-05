#include "Controller.h"
#include "State.h"
#include "Transition.h"
#include "Pawn.h"
#include "AngleUtilities.h"

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
Controller::init(vector<DelegatorDesciption> defaultReactions, 
                 vector<DelegatorDesciption> specificReactions)
{
  map<uint,vector<Delegator*>> defaults;

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
  m_actualState->onMessage((uint)MESSAGES::OnExit);
  m_actualState = m_states[newState];
  m_actualState->onMessage((uint)MESSAGES::OnEnter);
}

void 
Controller::update(float delta)
{
  m_actualState->onMessage((uint)MESSAGES::OnUpdate);
}

void 
Controller::message(uint msg)
{
  m_actualState->onMessage(msg);
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
Controller::separate()
{
  auto pawn = getPawn();
  auto pos = pawn->getPosition();
  auto viewed = m_memory.getVariableAs<Harmony::vector<Harmony::Vector2f>>("viewed");
  if(!viewed){
    return;
  }
  for(auto& view : *viewed){
    auto vec = pos-view;
    vec = vec.normalized()*(1.f/vec.magnitud());
    pawn->acelerate(vec);
  }
}

void 
Controller::goToPoint()
{
  auto position = m_pawn->getPosition();
  auto pointToGo = m_memory.getVariableAs<Dimencion>("pointToGo");

  if(!pointToGo){
    message(static_cast<uint>(MESSAGES::OnFinish));
    return;
  }

  auto distance = *pointToGo-position;

  if(size(distance) < *m_memory.getVariableAs<float>("aceptanceRadius")){
    message(static_cast<uint>(MESSAGES::OnFinish));
  }

  goToPoint(*pointToGo);
}

void Controller::lookTo()
{
  auto pawn = getPawn();
  auto position = pawn->getPosition();
  auto direction = VectorToAngle(pawn->getDirection());
  auto pointToGo = m_memory.getVariableAs<Dimencion>("pointToGo");

  if(!pointToGo){
    return;
  }

  float directionToGo = VectorToAngle(*pointToGo-position);
  float rotation = directionToGo-direction;

  pawn->rotate(rotation);
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
