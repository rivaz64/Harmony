#pragma once
#include "Prerequisites.h"

namespace Harmony{

/**
 * @brief a cell in the maze and the paths it has
*/

namespace MAZE_CELL{
enum E : char
{
  NONE = 0,
  UP = 1,
  RIGHT = 2,
  DOWN = 4,
  LEFT = 8
};
}

class Maze
{
 public:

  /**
   * @brief generates a maze with the given dimencions
   * @param x 
   * @param y 
  */
  void
  generate(uint x, uint y, uint seed);

  inline void
  setValueAt(uint x,uint y,MAZE_CELL::E value)
  {
    auto oneDimPos = x+y*sizeX;
    grid[oneDimPos/2] = static_cast<MAZE_CELL::E>(grid[oneDimPos/2] | static_cast<MAZE_CELL::E>(value<<((oneDimPos%2)*4)));
  }

  MAZE_CELL::E
  getValueAt(uint x,uint y)
  {
    auto oneDimPos = x+y*sizeX;
    return static_cast<MAZE_CELL::E>(grid[oneDimPos/2]>>((oneDimPos%2)*4));
  }

 private:
  
  /**
   * @brief the grid containing the maze
  */
  vector<MAZE_CELL::E> grid;

  uint sizeX;
  uint sizeY;
};

}

