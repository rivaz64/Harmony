#include "Quad.h"
#include "Triangle.h"

namespace Harmony{

bool 
Quad::isPointInside(const Dimencion& point, uint& side) const
{
  side = getSide(point);
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
Quad::getSide(const Dimencion& point) const
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

vector<Dimencion> 
Quad::getPoints()
{
  return {m_center+Dimencion(m_radius,m_radius),
          m_center+Dimencion(-m_radius,m_radius),
          m_center+Dimencion(-m_radius,-m_radius),
          m_center+Dimencion(m_radius,-m_radius)};
}

vector<Triangle*> 
Quad::triangulate()
{
  auto points = getPoints();
  return {new Triangle(points[0],points[1],points[2]),
          new Triangle(points[2],points[3],points[0])};
}

}

