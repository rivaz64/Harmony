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
  UP = 64,
  DOWN = 128
};
}

//struct Coord{
//  uint x;
//  uint y;
//};
//
//struct Coord3D :
//  public Coord{
//  uint z;
//
//};

class Grid{

 public:
  /**
   * @brief adds a passage to this position
   * @param x 
   * @param y 
   * @param value 
  */
  virtual void
  setValueAt(uint x, uint y,uint value){}

  /**
   * @brief gets the passages at this position
   * @param x 
   * @param y 
   * @return 
  */
  virtual uint
  getValueAt(uint x, uint y){return 0;}

  /**
   * @brief moves coordinates in a direction
   * @param x 
   * @param y 
   * @param dir 
  */
  virtual void
  move(uint& x, uint& y, const uint dir){}

  /**
   * @brief gets the inverse of the direction
   * @param dir 
   * @return 
  */
  virtual uint
  inverse(uint dir){return 0;}

  /**
   * @brief creates a conection between to cells
   * @param x 
   * @param y 
   * @param dir 
  */
  inline void 
  mark(uint& x, uint& y, const uint dir){
    setValueAt(x, y, dir);
    move(x, y, dir);
    setValueAt(x, y, inverse(dir));
  }

  /**
   * @brief gets the posible moves a cell has
   * @param x 
   * @param y 
   * @return 
  */
  virtual vector<uint>
  checkMoves(const uint x, const  uint y){return {};}

  virtual vector<uint>
  checkMarkedMoves(const uint x, const uint y){return {};}

  uint sizeX;
  uint sizeY;
};

class ExelGrid :
  public Grid
{
 public:
  ExelGrid() = default;
  
  ExelGrid(uint x, uint y){
    sizeX = x;
    sizeY = y;
    cells.clear();
    cells.resize(x*y);
  }

  void
  setValueAt(uint x, uint y,uint value) override;

  //inline void
  //setValueAt(uint x,uint y,MAZE_CELL::E value)
  //{
  //  auto oneDimPos = x+y*sizeX;
  //  cells[oneDimPos] = static_cast<EXEL_CELL::E>(cells[oneDimPos] | static_cast<MAZE_CELL::E>(value));
  //}

  uint
  getValueAt(uint x, uint y) override;

  //EXEL_CELL::E
  //getValueAt(uint x,uint y)
  //{
  //  auto oneDimPos = x+y*sizeX;
  //  return static_cast<EXEL_CELL::E>(cells[oneDimPos]);
  //}

  void
  move(uint& x, uint& y, const uint dir) override;

  uint
  inverse(uint dir) override;

  vector<uint>
  checkMoves(const uint x, const  uint y) override;

  vector<uint>
  checkMarkedMoves(const uint x, const uint y) override;

 private:
  /**
   * @brief the grid containing the maze
  */
  vector<EXEL_CELL::E> cells;
};

class QuadGrid : 
  public Grid
{
 public:

  QuadGrid() = default;
  
  QuadGrid(uint x, uint y){
    sizeX = x;
    sizeY = y;
    cells.clear();
    cells.resize((x*y)/2);
  }

  void
  setValueAt(uint x, uint y,uint value) override;

  //inline void
  //setValueAt(uint x,uint y,MAZE_CELL::E value)
  //{
  //  auto oneDimPos = x+y*sizeX;
  //  cells[oneDimPos/2] = static_cast<MAZE_CELL::E>(cells[oneDimPos/2] | static_cast<MAZE_CELL::E>(value<<((oneDimPos%2)*4)));
  //}

  uint
  getValueAt(uint x, uint y) override;

  //MAZE_CELL::E
  //getValueAt(uint x,uint y)
  //{
  //  auto oneDimPos = x+y*sizeX;
  //  return static_cast<MAZE_CELL::E>((cells[oneDimPos/2]>>((oneDimPos%2)*4))%16);
  //}

  void
  move(uint& x, uint& y, const uint dir) override;

  virtual uint
  inverse(uint dir) override;

  vector<uint>
  checkMoves(const uint x, const  uint y) override;

  vector<uint>
  checkMarkedMoves(const uint x, const uint y) override;

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
   * @brief the grid the maze is going to use
   * @param grid 
  */
  void
  init(Grid* grid);

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

 private:
  
  Grid* m_grid;
};

}

