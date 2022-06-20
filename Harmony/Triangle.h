#pragma once
#include "Prerequisites.h"
#include "Figure.h"

namespace Harmony{

class Triangle :
  public Figure
{
 public:

  Triangle() = default;

  Triangle(Dimencion p1, Dimencion p2, Dimencion p3);
    
  uint 
  getSide(const Dimencion& point) const override;

  bool
  isPointInside(const Dimencion& point, uint& side) const override;
  

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

  /**
   * @brief if 2 triangles are the same
   * @param tri 
   * @return 
  */
  bool
  operator==(const Triangle& tri) const;

  /**
   * @brief if 2 triangles have a same edge
   * @param tri 
   * @return 
  */
  bool
  areAdjacent(const Triangle& tri) const;

  ///**
  // * @brief if a point is inside the triange
  // * @param point 
  // * @return 
  //*/
  //bool 
  //isPointInside(const Dimencion& point);

  /**
   * @brief the normal of an edge tooking to the inside of the triangle
   * @param n 
   * @return 
  */
  Dimencion
  normalOfEdgeToInside(uint n);

  /**
   * @brief the normal of an edge tooking to the outside of the triangle
   * @param n 
   * @return 
  */
  Dimencion
  normalOfEdgeToOutside(uint n);

 public:
  
  Dimencion point1;
  Dimencion point2;
  Dimencion point3;
};

}


