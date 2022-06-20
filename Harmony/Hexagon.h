#pragma once
#include "Prerequisites.h"
#include "Figure.h"

namespace Harmony{

namespace HEX_SIDE{
enum E : unsigned char
{
  NONE = 0,
  UP = 1,
  UP_RIGHT = 2,
  UP_LEFT = 4,
  DOWN = 8,
  DOWN_LEFT = 16,
  DOWN_RIGHT = 32,
  ALL = 255
};
}

/**
 * @brief a class for an exagonal area
*/
class Hexagon :
  public Figure
{
  public:

  Hexagon(Dimencion center, float size) :
    m_center(center), m_radius(size){}

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

