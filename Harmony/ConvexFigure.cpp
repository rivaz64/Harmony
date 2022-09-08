#include "ConvexFigure.h"
#include "Triangle.h"

namespace Harmony
{

ConvexFigure::ConvexFigure(const Triangle& tri)
{
  vector<Dimencion> points;
  points.resize(3);
  points[0] = tri.point1;
  points[1] = tri.point2;
  points[2] = tri.point3;
  addPoints(points);
}

void 
ConvexFigure::operator=(const Triangle& tri)
{
  vector<Dimencion> points;
  points.resize(3);
  points[0] = tri.point1;
  points[1] = tri.point2;
  points[2] = tri.point3;
  addPoints(points);
}

uint
ConvexFigure::getSide(const Dimencion& point) const
{
  vector<float> angles;
  auto angle = VectorToAngle(point-m_center);
  int numOfPoints = m_points.size();
  if(angle < VectorToAngle(m_points[0]-m_center)){
    return numOfPoints-1;
  }
  for(int pointNum = 1; pointNum<numOfPoints; ++pointNum){
    if(angle < VectorToAngle(m_points[pointNum]-m_center)){
      return pointNum-1;
    }
  }
  return numOfPoints-1;
}

bool 
ConvexFigure::isPointInside(const Dimencion& point, uint& side) const
{
  side = getSide(point);
  auto dif = point-m_center;
  Vector2f intersection;
  return !Vector2f::intersect(m_points[side],m_points[(side+1)%m_points.size()],m_center,point,intersection);
}

}

