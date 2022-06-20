#pragma once
#include "Prerequisites.h"
#include "Figure.h"

namespace Harmony{

namespace QUAD_SIDE{
enum E : unsigned char
{
  NONE = 0,
  UP = 1,
  RIGHT = 2,
  DOWN = 4,
  LEFT = 8,
  ALL = 15
};
}

/**
 * @brief class for a quad area
*/
class Quad :
  public Figure
{
 public:

  Quad(Dimencion center, float size) :
    m_center(center), m_radius(size/2.f){}

  bool
  isPointInside(Dimencion point, uint& side) override;

  uint 
  getSide(Dimencion point) override;


 private:
  /**
   * @brief the center of the quad
  */
  Dimencion m_center;

  /**
   * @brief half the size of a side
  */
  float m_radius;
};

}


