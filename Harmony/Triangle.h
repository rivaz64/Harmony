#pragma once
#include "Prerequisites.h"

namespace Harmony{

class Triangle
{
 public:

  Triangle(Vector2f p1, Vector2f p2, Vector2f p3) :
    point1(p1), point2(p2), point3(p3) {}

  /**
   * @brief calculates the circumcenter of this triangle
   * @return 
  */
  Vector2f
  circumcenter();

  /**
   * @brief if a point beongs to this triangle
   * @param v 
   * @return 
  */
  bool
  hasPoint(const Vector2f& v);

  /**
   * @brief if an edge beongs to this triangle
   * @param v1 
   * @param v2 
   * @return 
  */
  bool
  hasEdge(const Vector2f& v1, const Vector2f& v2);

 public:
  
  Vector2f point1;
  Vector2f point2;
  Vector2f point3;
};

}


