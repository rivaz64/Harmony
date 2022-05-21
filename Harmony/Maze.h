#pragma once
#include "Prerequisites.h"

namespace Harmony{

/**
 * @brief a cell in the maze and the paths it has
*/

namespace MAZE_CELL{
enum E : unsigned char
{
  NONE = 0,
  UP = 1,
  RIGHT = 2,
  DOWN = 4,
  LEFT = 8
};
}

class Grid
{
 public:
  
  Grid(uint x, uint y){
    sizeX = x;
    sizeY = y;
    cells.clear();
    cells.resize((x*y)/2);
  }

  inline void
  setValueAt(uint x,uint y,MAZE_CELL::E value)
  {
    auto oneDimPos = x+y*sizeX;
    cells[oneDimPos/2] = static_cast<MAZE_CELL::E>(cells[oneDimPos/2] | static_cast<MAZE_CELL::E>(value<<((oneDimPos%2)*4)));
  }

  MAZE_CELL::E
  getValueAt(uint x,uint y)
  {
    auto oneDimPos = x+y*sizeX;
    return static_cast<MAZE_CELL::E>((cells[oneDimPos/2]>>((oneDimPos%2)*4))%16);
  }

 public:
  
  uint sizeX;
  uint sizeY;

 private:
  /**
   * @brief the grid containing the maze
  */
  vector<MAZE_CELL::E> cells;
};

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

  void
  backtracker(uint seed);

  void
  aldousBroder(uint seed);

  

 private:
  
  Grid grid;
};

}

