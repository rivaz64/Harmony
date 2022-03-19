#pragma once

#include "ForDecHarmony.h"
#include "Vector2f.h"

namespace Harmony{

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
   * @brief gets the direction of this pawn
   * @return 
  */
  virtual Vector2f
  getDirection();

  /**
   * @brief sets the position of this pawn
   * @return 
  */
  virtual Vector2f
  setPosition(const Vector2f&){}

  /**
   * @brief sets the velocity of this pawn
   * @return 
  */
  virtual Vector2f
  setVelocity(const Vector2f&){}

  /**
   * @brief sets the direction of this pawn
   * @return 
  */
  virtual Vector2f
  setDirection(const Vector2f&){}

 private:
  
  /**
   * @brief this is controlling this pawn
  */
  Controller* m_controller; 
};

}


