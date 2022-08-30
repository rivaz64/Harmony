#pragma once
#include "Prerequisites.h"

namespace Harmony{

/**
 * @brief interface for 2D figures
*/
class Figure
{
 public:

  /**
   * @brief the side from the center where the point is
   * @param point 
   * @return 
  */
  virtual uint 
  getSide(const Dimencion& point) const {return 0;}

  /**
   * @brief if a point is inside the figure
   * @param point 
   * @return 
  */
  virtual bool
  isPointInside(const Dimencion& point, uint& side) const {return false;}

  inline void
  setCenter(const Dimencion& center){
    m_center = center;
  }

  inline Dimencion
  getCenter() const{
    return m_center;
  }
 
 protected:
  /**
   * @brief the center of the figure
  */
  Dimencion m_center;
};

}


