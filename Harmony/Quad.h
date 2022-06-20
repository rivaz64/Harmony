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

  Quad() = default;

  Quad(const Dimencion& center, float size) :
     m_radius(size/2.f){m_center=center;}

  bool
  isPointInside(const Dimencion& point, uint& side) override;

  uint 
  getSide(const Dimencion& point) override;

  inline void
  setSize(float size){
    m_radius = size/2.f;
  }

  inline float
  getSize(){
    return m_radius*2.f;
  }

 private:

  /**
   * @brief half the size of a side
  */
  float m_radius;
};

}


