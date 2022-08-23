#include "Controler.h"
#include "State.h"
#include "Transition.h"
#include "Pawn.h"
#include "AngleUtilities.h"

namespace Harmony{

Controler::Controler(const vector<STATES::E>& states)                  
{
  for(auto state : states){
    m_states.insert({state,new State});
  }
  
  //m_actualState = states.begin()->first;
}

Controler::~Controler()
{
  for(auto& state : m_states){
    delete state.second;
    state.second = nullptr;
  }
  
}

void 
Controler::init(vector<DelegatorDesciption> defaultReactions, 
                 vector<DelegatorDesciption> specificReactions)
{
  map<uint,vector<Action*>> defaults;

  for(auto& desc : defaultReactions){
    defaults.insert({desc.message,desc.toState});
  }

  for(auto& state: m_states){
    state.second->m_reactions = defaults;
  }

  for(auto& desc : specificReactions){
    m_states[desc.fromState]->m_reactions[desc.message] = desc.toState;
  }

  m_states[m_actualState]->onMessage(this,MESSAGES::OnEnter);
}

void
Controler::changeToState(STATES::E newState)
{
  m_states[m_actualState]->onMessage(this,MESSAGES::OnExit);
  m_actualState = newState;
  m_states[m_actualState]->onMessage(this,MESSAGES::OnEnter);
}

void 
Controler::update(float delta)
{
  deltaTime = delta;

  m_states[m_actualState]->onMessage(this,MESSAGES::OnUpdate);
}

void 
Controler::message(MESSAGES::E msg)
{
  m_states[m_actualState]->onMessage(this,msg);
}

void 
Controler::remember(MEMENTOS::E type, Memento* memory)
{
  if(m_memory.find(type) == m_memory.end()){
    m_memory.insert({type,{}});
  }
  m_memory[type].push_back(memory);
}

void
Controler::newRandomPointToGo()
{
  auto location = m_pawn->getPosition();
  auto direction = m_pawn->getDirection();
  auto newPoint = location+direction*m_wanderDelta;
  auto wanderPoint = reachablePointInRadius(newPoint,m_wanderRadius);
  m_variables.addVariableOfType<Dimencion>("pointToGo");
  m_variables.setVariableAs<Dimencion>("pointToGo",wanderPoint);
}

void
Controler::separate()
{
  const auto& separationForze = *m_variables.getVariableAs<float>("separationForze");
  auto pawn = getPawn();
  auto pos = pawn->getPosition();
  auto viewed = m_variables.getVariableAs<Harmony::vector<Harmony::Pawn*>>("viewed");
  if(!viewed){
    return;
  }
  for(auto& view : *viewed){
    auto multi = ((Vector2f::dot(view->getVelocity().normalized(),pos-view->getPosition())+1.f)/2.f)*.0625f+.9375f;
    
    auto vec = pos-view->getPosition();
    vec = vec.normalized()*(separationForze/vec.magnitud());
    pawn->acelerate(vec*multi);//*multi);
    
    
  }
}

void 
Controler::align()
{
  auto pawn = getPawn();
  auto pos = pawn->getPosition();
  auto pawnDir = pawn->getDirection();
  auto viewed = m_variables.getVariableAs<Harmony::vector<Harmony::Pawn*>>("viewed");
  if(!viewed){
    return;
  }
  Dimencion dir;
  memset(&dir,0,sizeof(Dimencion));
  for(auto& view : *viewed){
    dir += view->getDirection();
  }
  
  pawn->rotate(angleBetween(VectorToAngle(pawnDir),VectorToAngle(dir)));
}

void
Controler::coher()
{
  const auto& cohercionForze = *m_variables.getVariableAs<float>("cohercionForze");
  auto pawn = getPawn();
  auto pos = pawn->getPosition();
  auto pawnDir = pawn->getDirection();
  auto viewed = m_variables.getVariableAs<Harmony::vector<Harmony::Pawn*>>("viewed");
  if(!viewed || viewed->size()==0){
    return;
  }
  Dimencion center;
  memset(&center,0,sizeof(Dimencion));
  for(auto& view : *viewed){
    center += view->getPosition();
  }
  center /= static_cast<float>(viewed->size());
  pawn->acelerate((center-pos).normalized()*cohercionForze);
}

void 
Controler::goToPoint()
{
  auto position = m_pawn->getPosition();
  auto pointToGo = m_variables.getVariableAs<Dimencion>("pointToGo");
  auto& aceptanceRadius = *m_variables.getVariableAs<float>("aceptanceRadius");
  if(!pointToGo){
    message(MESSAGES::OnFinish);
    return;
  }
  
  auto distance = *pointToGo-position;
  
  if(size(distance) < aceptanceRadius){
    message(MESSAGES::OnFinish);
  }
  
  goToPoint(*pointToGo);
}

void 
Controler::lookTo()
{
  auto pawn = getPawn();
  auto position = pawn->getPosition();
  auto direction = VectorToAngle(pawn->getDirection());
  auto pointToGo = m_variables.getVariableAs<Dimencion>("pointToGo");
  
  if(!pointToGo){
    return;
  }
  
  float directionToGo = VectorToAngle(*pointToGo-position);
  float rotation = directionToGo-direction;
  
  pawn->rotate(rotation);
}

void 
Controler::wait()
{
  auto& timer = *m_variables.getVariableAs<float>("timer");
  auto& timeToWait = *m_variables.getVariableAs<float>("timeToWait");
  timer += deltaTime;
  if(timer>timeToWait){
    message(MESSAGES::OnFinish);
  }
  
}

void 
Controler::restart()
{
  auto& timer = *m_variables.getVariableAs<float>("timer");
  timer = 0;
}

void 
Controler::nextPointPath()
{
  auto& pointToGo = *m_variables.getVariableAs<Vector2f>("pointToGo");
  auto& path = *m_variables.getVariableAs<list<Vector2f>>("path");
  if(path.size()>0){
    pointToGo = path.front();
    path.pop_front();
  }
}

void 
Controler::nextPointPatrol()
{
  auto& pointToGo = *m_variables.getVariableAs<Vector2f>("pointToGo");
  auto& path = *m_variables.getVariableAs<list<Vector2f>>("path");
  if(path.size()>0){
    pointToGo = path.front();
    path.push_back(pointToGo);
    path.pop_front();
  }
}

void
Controler::goToPoint(const Dimencion& point)
{
  print("goToPoint does nothing");
}

Dimencion 
Controler::reachablePointInRadius(const Dimencion& point, float radius)
{
  print("reachablePointInRadius nothing");
  return Dimencion();
}

}
