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

  Hexagon() = default;

  Hexagon(const Dimencion& center, float size) :
    m_radius(size){m_center=center;}

  bool
  isPointInside(const Dimencion& point, uint& side) const override;

  uint 
  getSide(const Dimencion& point) const override;

  inline void
  setSize(float size){
    m_radius = size;
  }

  inline float
  getSize(){
    return m_radius;
  }

 private:

  /**
   * @brief half the size of a side
  */
  float m_radius;
};


}

