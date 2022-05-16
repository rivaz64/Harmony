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
   * @brief rezises the maze to the given dimencions
   * @param x 
   * @param y 
  */
  void
  init(uint x, uint y);

  /**
   * @brief generates a maze using binary tree
   * @param seed 
   * @param probabolityX the probability to go in x
   * @param probabolityY the probability to go in y
  */
  void
  binaryTree(uint seed, uint probabolityX, uint probabolityY);

  /**
   * @brief generates a maze using sidewinder
   * @param seed 
   * @param hallLength he probability of a wall in X
  */
  void
  sidewinder(uint seed, uint hallLength);

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

