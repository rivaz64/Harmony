#include "Triangle.h"

namespace Harmony{

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
Triangle::hasPoint(const Vector2f& v)
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
Triangle::hasEdge(const Vector2f& v1, const Vector2f& v2)
{
  auto ref = &point1;
  for(uint i = 0; i<3; ++i){
    if((v1 == *(ref+i) && v2 == *(ref+(i+1)%3)) || (v2 == *(ref+i) && v1 == *(ref+(i+1)%3))){
      return true;
    }
  }
  return false;
}

}

