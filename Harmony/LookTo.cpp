#include "LookTo.h"
#include "Controller.h"
#include "Pawn.h"
#include "AngleUtilities.h"

namespace Harmony{

void 
LookTo::update(Controller* controller, float delta)
{
  auto pawn = controller->getPawn();
  auto position = pawn->getPosition();
  auto direction = VectorToAngle(pawn->getDirection());

  auto pointToGo = controller->m_memory.getVariableAs<Vector2f>("pointToGo");
  if(!pointToGo){
    return;
  }

  float directionToGo = VectorToAngle(*pointToGo-position);
  float rotation = directionToGo-direction;

  pawn->rotate(rotation);
}

}

