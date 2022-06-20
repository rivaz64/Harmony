#include "Quad.h"

namespace Harmony{

bool 
Quad::isPointInside(const Dimencion& point, uint& side)
{
  auto s = getSide(point);
  auto dif = point-m_center;
  switch (side)
  {
  case QUAD_SIDE::UP:
    return point.y < m_center.y+m_radius;
  case QUAD_SIDE::DOWN:
    return point.y > m_center.y-m_radius;
  case QUAD_SIDE::RIGHT:
    return point.x < m_center.x+m_radius;
  case QUAD_SIDE::LEFT:
    return point.x > m_center.x-m_radius;
  default:
    return false;
  }
}

uint
Quad::getSide(const Dimencion& point)
{
  auto dir = point-m_center;
  if(abs(dir.x)>abs(dir.y)){
    if(dir.x>=0){
      return QUAD_SIDE::RIGHT;
    }
    else{
      return QUAD_SIDE::LEFT;
    }
  }
  else{
    if(dir.y>=0){
      return QUAD_SIDE::UP;
    }
    else{
      return QUAD_SIDE::DOWN;
    }
  }
}

}

