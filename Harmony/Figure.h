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
  getSide(Dimencion point) {return 0;}

  /**
   * @brief if a point is inside the figure
   * @param point 
   * @return 
  */
  virtual bool
  isPointInside(Dimencion point, uint& side){return false;}


};

}


