#pragma once
#include "Grid.h"

namespace Harmony{

class MultiGrid :
  public Grid
{
 public:
  
  void
  setValueAt(uint x, uint y, uint z, uint value);

  void
  unsetValueAt(uint x, uint y, uint z, uint value);

  uint
  getValueAt(uint x, uint y, uint z);

  Grid*
  getGrid(uint z);

  map<uint,uint>
  getAdjacentCells(const uint id) override;

  float
  getDistance(uint id);

  void 
  calculateDistances();

  void
  addLink(NavLink* link);

  void
  setGoal(uint goal) override;

  inline void 
  addGrid(Grid* newGrid)
  {
    m_grids.push_back(newGrid);
  }

 protected:
  
  vector<Grid*> m_grids;

  /**
   * @brief all the links that are conected to the node
  */
  vector<map<uint,vector<NavLink*>>> m_links;

  vector<vector<pair<float,NavLink*>>> m_distances;
};

}


