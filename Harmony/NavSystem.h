#pragma once
#include "Prerequisites.h"

namespace Harmony{

class Figure;

/**
 * @brief class for navigating
*/
class NavSystem
{

 public:
  
  NavSystem(Grid* grid) :
    m_grid(grid){}

  void
  addPawn(Pawn* pawn);

 private:

  /**
   * @brief the pawns using this navSystem
  */
  map<Pawn*,Figure*> m_pawns; 

  /**
   * @brief the navmesh the system is going to use
  */
  Grid* m_grid;
};

}


