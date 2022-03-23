#include "GoToPoint.h"
#include "Controller.h"
#include "Pawn.h"
#include "Vector2f.h"
#include "AngleUtilities.h"
namespace Harmony{

void 
GoToPoint::update(Controller* controller,float delta)
{
  auto pawn = controller->getPawn();
  auto position = pawn->getPosition();
  auto velocity = pawn->getVelocity();
  auto pointToGo = controller->m_memory.getVariableAs<Vector2f>("pointToGo");

  if(!pointToGo){
    return;
  }

  auto distance = *pointToGo-position;

  if(distance.magnitud()<aceptanceRadius){
    //onArrive();
  }

  auto desiredVelocity = distance.normalized()*pawn->getMaxVelocity();
  auto desiredAceleration = desiredVelocity-velocity;
  pawn->acelerate(desiredAceleration);
}

}
