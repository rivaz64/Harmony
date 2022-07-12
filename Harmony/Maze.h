#pragma once
#include "Prerequisites.h"

namespace Harmony{

struct Coord{
  uint x;
  uint y;
};
//
//struct Coord3D :
//  public Coord{
//  uint z;
//
//};

class Maze
{
 public:

  /**
   * @brief the grid the maze is going to use
   * @param grid 
  */
  void
  init(Grid* grid,uint area);

  /**
   * @brief in each cell decides if go up or roght
   * @param seed 
   * @param probabolityX the probability to go in x
   * @param probabolityY the probability to go in y
  */
  void
  binaryTree(uint seed);

  /**
   * @brief makes an horizontal passage and decides in one of the cells of the passage to go up
   * @param seed 
   * @param hallLength he probability of a wall in X
  */
  void
  sidewinder(uint seed, uint hallLength);

  /**
   * @brief random walk until there is no other place to walk, it returns until it can continue
   * @param seed 
  */
  void
  backtracker(uint seed);

  /**
   * @brief random walk, connects only if the new cell is not in the maze
   * @param seed 
  */
  void
  aldousBroder(uint seed);

  /**
   * @brief select a random cells and does random walk until if gets to the maze
   * @param seed 
  */
  void
  wilson(uint seed);

  void
  kruskal(uint seed, uint areas);

  /**
   * @brief adds directions to dead points
   * @param p the percentage of points to clear
  */
  void
  clearDeadPoints(float p);

 private:
  
  /**
   * @brief the area to be filled by the maze
  */
  uint m_area; 

  /**
   * @brief the grid where the maze is going to be drawn
  */
  Grid* m_grid;

  /**
   * @brief the cells that only have one direction
  */
  list<Coord> deadPoints; 
};

}

