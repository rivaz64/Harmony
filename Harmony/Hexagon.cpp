#include "Hexagon.h"
#include "AngleUtilities.h"
namespace Harmony{

bool 
Hexagon::isPointInside(const Dimencion& point, uint& side) const
{
  side = getSide(point);
  auto dif = point-m_center;
  switch (side)
  {
  case HEX_SIDE::UP:
    return point.y<m_center.y+m_radius*sqrtf(3)/2.f;
  case HEX_SIDE::DOWN:
    return point.y>m_center.y-m_radius*sqrtf(3)/2.f;
  case HEX_SIDE::UP_RIGHT:
    return dif.x/m_radius+dif.y/(m_radius*sqrtf(3))<1;
  case HEX_SIDE::UP_LEFT:
    return -dif.x/m_radius+dif.y/(m_radius*sqrtf(3))<1;
   case HEX_SIDE::DOWN_RIGHT:
    return dif.x/m_radius-dif.y/(m_radius*sqrtf(3))<1;
  case HEX_SIDE::DOWN_LEFT:
    return -dif.x/m_radius-dif.y/(m_radius*sqrtf(3))<1;
  default:
    return false;
  }
}

uint 
Hexagon::getSide(const Dimencion& point) const
{
  auto dir = point-m_center;
  auto angle = VectorToAngle(dir);
  if(angle > PI*2.f/3.f){
    return HEX_SIDE::UP_LEFT;
  }
  else if(angle > PI*1.f/3.f){
    return HEX_SIDE::UP;
  }
  else if(angle > 0){
    return HEX_SIDE::UP_RIGHT;
  }
  else if(angle > -PI*1.f/3.f){
    return HEX_SIDE::DOWN_RIGHT;
  }
  else if(angle > -PI*2.f/3.f){
    return HEX_SIDE::DOWN;
  }
  else{
    return HEX_SIDE::DOWN_LEFT;
  }
}

vector<Dimencion> 
Hexagon::getPoints()
{
  float externRadius = m_radius*2.f/sqrt(3);
  return {m_center+Dimencion(externRadius,0),
          m_center+Dimencion(externRadius*cos(PI/3.f),externRadius*sin(PI/3.f)),
          m_center+Dimencion(externRadius*cos(2.f*PI/3.f),externRadius*sin(2.f*PI/3.f)),
          m_center+Dimencion(-externRadius,0),
          m_center+Dimencion(externRadius*cos(4.f*PI/3.f),externRadius*sin(4.f*PI/3.f)),
          m_center+Dimencion(externRadius*cos(5.f*PI/3.f),externRadius*sin(5.f*PI/3.f))};
}

vector<Triangle*> 
Hexagon::triangulate()
{
  return {};
}


}
