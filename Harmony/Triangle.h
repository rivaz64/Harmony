#pragma once
#include "Prerequisites.h"

namespace Harmony{

class Triangle
{
 public:

  Triangle(Dimencion p1, Dimencion p2, Dimencion p3) :
    point1(p1), point2(p2), point3(p3) {}

  /**
   * @brief calculates the circumcenter of this triangle
   * @return 
  */
  Dimencion
  circumcenter();

  /**
   * @brief if a point beongs to this triangle
   * @param v 
   * @return 
  */
  bool
  hasPoint(const Dimencion& v) const;

  /**
   * @brief if an edge beongs to this triangle
   * @param v1 
   * @param v2 
   * @return 
  */
  bool
  hasEdge(const Dimencion& v1, const Dimencion& v2) const;

  bool
  operator==(const Triangle& tri) const;

 public:
  
  Dimencion point1;
  Dimencion point2;
  Dimencion point3;
};

}


