#pragma once
#include "Prerequisites.h"
#include "Grid.h"

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
  LEFT = 8,
  ALL = 15
};
}

/**
 * @brief a grid of squares
*/
class QuadGrid : 
  public Grid
{
 public:

  QuadGrid() = default;
  
  QuadGrid(uint x, uint y,float cellSize, const Dimencion& ofset);

  void
  setValueAt(uint x, uint y,uint value) override;

  uint
  getValueAt(uint x, uint y) override;

  void
  move(uint& x, uint& y, const uint dir) override;

  virtual uint
  inverse(uint dir) override;

  vector<uint>
  checkMoves(const uint x, const  uint y) override;

  vector<uint>
  checkMarkedMoves(const uint x, const uint y) override;

  vector<uint>
  checknewMoves(const uint x, const uint y) override;

  void
  useFigure(const uint x, const uint y) override;

 private:
  /**
   * @brief the grid containing the maze
  */
  vector<MAZE_CELL::E> cells;


};

}

