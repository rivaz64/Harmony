#include "Triangle.h"
#include "AngleUtilities.h"

namespace Harmony{

Dimencion 
Triangle::center()
{
  return (point1+point2+point3)/3.f;
}

Vector2f
Triangle::circumcenter()
{
  auto midpoint1 = (point1+point2)/2.f;
  auto midpoint2 = (point1+point3)/2.f;

  auto dir1 = (point1-point2).normalized();
  auto dir2 = (point1-point3).normalized();

  dir1 = Vector2f(-dir1.y,dir1.x);
  dir2 = Vector2f(-dir2.y,dir2.x);

  Vector2f center;

  Vector2f::intersect(midpoint1+dir1,
                      midpoint1-dir1,
                      midpoint2+dir2,
                      midpoint2-dir2,
                      center);

  return center;
}

bool 
Triangle::hasPoint(const Vector2f& v) const
{
   auto ref = &point1;
  for(uint i = 0; i<3; ++i){
    if(v == *(ref+i)){
      return true;
    }
  }
  return false;
}

bool 
Triangle::hasEdge(const Vector2f& v1, const Vector2f& v2) const
{
  return hasPoint(v1) && hasPoint(v2);
}

bool 
Triangle::operator==(const Triangle& tri) const
{
  return hasPoint(tri.point1) && hasPoint(tri.point2) && hasPoint(tri.point3);
}

bool
Triangle::areAdjacent(const Triangle& tri) const
{
  return hasEdge(tri.point1,tri.point2) || hasEdge(tri.point3,tri.point2) || hasEdge(tri.point1,tri.point3);
}

bool
Triangle::isPointInside(const Dimencion& point)
{
  auto angle1 = VectorToAngle(point1-point);
  auto angle2 = VectorToAngle(point2-point);
  auto angle3 = VectorToAngle(point3-point);
  auto totalAngle = abs(angleBetween(angle1,angle2))+
                    abs(angleBetween(angle3,angle2))+
                    abs(angleBetween(angle1,angle3));
  return abs(totalAngle-PI*2.f) > .01f;
}

}

