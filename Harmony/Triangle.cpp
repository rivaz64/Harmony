#include "Triangle.h"
#include "AngleUtilities.h"

namespace Harmony{

Triangle::Triangle(Dimencion p1, Dimencion p2, Dimencion p3) 
{ 
  m_center = (p1+p2+p3)/3.f;
  auto angle1 = VectorToAngle(p1-m_center);
  auto angle2 = VectorToAngle(p2-m_center);
  auto angle3 = VectorToAngle(p3-m_center);
  point1 = p1;
  point2 = p2;
  point3 = p3;
  if(angle2>angle1){
    swap(point1,point2);
    swap(angle1,angle2);
  }
  if(angle3>angle1){
    swap(point1,point3);
    swap(angle1,angle3);
  }
  if(angle3>angle2){
    swap(point3,point2);
    swap(angle3,angle2);
  }
}

uint 
Triangle::getSide(const Dimencion& point) const
{
  auto center = getCenter();
  auto angle1 = VectorToAngle(point1-center);
  auto angle2 = VectorToAngle(point2-center);
  auto angle3 = VectorToAngle(point3-center);
  auto angle = VectorToAngle(point-center);
  if(angle>angle1){
    return 3;
  }
  else if(angle>angle2){
    return 1;
  }
  else if(angle>angle3){
    return 2;
  }
  else{
    return 3;
  }

}

bool 
Triangle::isPointInside(const Dimencion& point, uint& side) const
{
  side = getSide(point);
  auto dif = point-m_center;
  Vector2f intersection;
  switch (side)
  {
  case 1:
    return !Vector2f::intersect(point1,point2,m_center,point,intersection);
  case 2:
    return !Vector2f::intersect(point2,point3,m_center,point,intersection);
  case 3:
    return !Vector2f::intersect(point3,point1,m_center,point,intersection);
  }
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

//bool
//Triangle::isPointInside(const Dimencion& point)
//{
//  auto angle1 = VectorToAngle(point1-point);
//  auto angle2 = VectorToAngle(point2-point);
//  auto angle3 = VectorToAngle(point3-point);
//  auto totalAngle = abs(angleBetween(angle1,angle2))+
//                    abs(angleBetween(angle3,angle2))+
//                    abs(angleBetween(angle1,angle3));
//  return abs(totalAngle-PI*2.f) < .0001f;
//}

Dimencion
Triangle::normalOfEdgeToInside(uint n)
{
  auto ref = &point1;
  auto vec = *(ref+(n+1)%3)-*(ref+n);
  vec.normalize();
  return Dimencion(-vec.y,vec.x);
}

Dimencion 
Triangle::normalOfEdgeToOutside(uint n)
{
  auto ref = &point1;
  auto vec = *(ref+(n+1)%3)-*(ref+n);
  vec.normalize();
  return Dimencion(vec.y,-vec.x);
}

float 
Triangle::angle(uint n)
{
  auto point = getPoint(n);
  auto vec1 = getPoint(n%3+1)-point;
  auto vec2 = getPoint((n+1)%3+1)-point;
  auto dot = Vector2f::dot(vec1,vec2);
  dot/=vec1.magnitud();
  dot/=vec2.magnitud();
  auto angle = acos(dot);
  return angle;
}

vector<Dimencion> 
Triangle::getPoints()
{
  return {point1,point2,point3};
}

vector<Triangle*>
Triangle::triangulate()
{
  return {this};
}

}

