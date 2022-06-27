#pragma once
#include "Prerequisites.h"
namespace Harmony{

//struct SurfaceNode{
//  uint id;
//  Figure* figure;
//};

/**
 * @brief a 2D surface divided in sections
*/
class Surface
{
 public:
  
  /**
   * @brief the node at where a point is in
   * @param point 
   * @param nodeId 
   * @return if the point is in the surface
  */
  virtual bool
  getCellAt(const Dimencion& point,uint& nodeId){return false;}

  virtual const Figure*
  getFigure(const uint id){return nullptr;}

  /**
   * @brief gets the cells that have acces to this one
   * @param id 
   * @return 
  */
  virtual map<uint,uint>
  getAdjacentCells(const uint id){return {};}

 protected:
};

}


