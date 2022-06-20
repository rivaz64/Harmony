#pragma once
#include "Grid.h"

namespace Harmony{

namespace EXEL_CELL{
enum E : unsigned char
{
  NONE = 0,
  UP = 1,
  UP_RIGHT = 2,
  UP_LEFT = 4,
  DOWN = 8,
  DOWN_LEFT = 16,
  DOWN_RIGHT = 32,
  //UP = 64,
  //DOWN = 128
  ALL = 255
};
}

/**
 * @brief a grid of exagons
*/
class ExelGrid :
  public Grid
{
 public:
  ExelGrid() = default;
  
  ExelGrid(uint x, uint y,float cellSize, const Dimencion& ofset);

  void
  setValueAt(uint x, uint y,uint value) override;

  uint
  getValueAt(uint x, uint y) override;

  void
  move(uint& x, uint& y, const uint dir) override;

  uint
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
  vector<EXEL_CELL::E> cells;
};

}

