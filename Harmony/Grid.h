#pragma once
#include "Prerequisites.h"
namespace Harmony{

/**
 * @brief interface for any kind of grid
*/
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

  /**
   * @brief get teh moves counting marked cells as collicions
   * @param x 
   * @param y 
   * @return 
  */
  virtual vector<uint>
  checkMarkedMoves(const uint x, const uint y){return {};}

  /**
   * @brief get the moves that are not of this cell
   * @param x 
   * @param y 
   * @return 
  */
  virtual vector<uint>
  checknewMoves(const uint x, const uint y){return {};}

  void
  getRandomCoords(uint& x, uint& y);

  uint sizeX;
  uint sizeY;
};

}
