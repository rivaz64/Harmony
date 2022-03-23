#include "Pawn.h"
#include "Vector2f.h"

#ifdef _DEBUG
#include "Debuger.h"
#endif

namespace Harmony{

Vector2f 
Pawn::getPosition()
{
   #ifdef _DEBUG
   print("get position not implemented");
   #endif
  return Vector2f::ZERO;
}

Vector2f Pawn::getVelocity()
{
  #ifdef _DEBUG
  print("get velocity not implemented");
  #endif
  return Vector2f::ZERO;
}

float
Pawn::getMaxVelocity()
{
  #ifdef _DEBUG
  print("get max velocity not implemented");
  #endif
  return 0.0f;
}

Vector2f Pawn::getDirection()
{
  #ifdef _DEBUG
  print("get direction not implemented");
  #endif
  return Vector2f::ZERO;
}

void 
Pawn::acelerate(const Vector2f&)
{
  #ifdef _DEBUG
  print("acelerate not implemented");
  #endif
}

void 
Pawn::rotate(float)
{
  #ifdef _DEBUG
  print("rotate not implemented");
  #endif
}

}

