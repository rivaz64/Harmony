#pragma once
#include "Prerequisites.h"
namespace Harmony{

//struct GraphNode{
//  uint id;
//  Figure* figure;
//};

/**
 * @brief a Graph with conected nodes
*/
class Graph
{
 public:
  
  /**
   * @brief the node at where a point is in
   * @param point 
   * @param nodeId 
   * @return if the point is in the Graph
  */
  virtual bool
  getCellAt(const Dimencion& point,uint& nodeId){return false;}

  virtual const Figure*
  getFigure(const uint id){return nullptr;}

  /**
   * @brief gets the cells that have acces to this one
   * @param id 
   * @return the first is the id, the second the other node
  */
  virtual map<uint,uint>
  getAdjacentNodes(const uint id){return {};}

  virtual float
  getDistance(uint id, uint otherId);

  virtual float
  getCost(uint id, uint idParent);

  virtual bool
  isAt(uint id, uint goalId);
};

}


