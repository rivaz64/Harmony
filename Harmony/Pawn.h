#pragma once

#include "Prerequisites.h"
#include "Vector2f.h"

namespace Harmony{

/**
 * @brief the interface class for what is going to be controlled
*/
class Pawn
{
 public:
  /**
   * @brief gets the position of this pawn
   * @return 
  */
  virtual Vector2f
  getPosition();

  /**
   * @brief gets the velocity of this pawn
   * @return 
  */
  virtual Vector2f
  getVelocity();

  /**
   * @brief gets the maximum velocity of this pawn can go
   * @return 
  */
  virtual float
  getMaxVelocity();

  /**
   * @brief gets the direction of this pawn
   * @return 
  */
  virtual Vector2f
  getDirection();

  /**
   * @brief acelerates the pawn in a certain direction;
   * @return 
  */
  virtual void
  acelerate(const Vector2f&);

  /**
   * @brief rotates the pawn in a certain direction;
   * @return 
  */
  virtual void
  rotate(float);

 private:
  
  /**
   * @brief this is controlling this pawn
  */
  Controller* m_controller; 

  friend class Manager;
};

}


