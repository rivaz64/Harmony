#include "AIController.h"
#include "Pawn.h"

namespace Harmony{

void 
AIController::newRandomPointToGo()
{
  auto location = m_pawn->getPosition();
  auto direction = m_pawn->getDirection();

  auto newPoint = location+direction*m_wanderDelta;
  auto randAngle = (float)rand()/(float)RAND_MAX;
  auto wanderPoint = Vector2f(cos(randAngle),sin(randAngle))*m_wanderRadius+newPoint;
  m_memory.addVariableOfType<Vector2f>("pointToGo");
  m_memory.setVariableAs<Vector2f>("pointToGo",wanderPoint);
}

}

