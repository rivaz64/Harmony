#pragma once

#include "Prerequisites.h"

namespace Harmony{

/**
 * @brief reacts to things in the world
*/
class Detector
{
 public:

  virtual void
  update(float delta){}

 protected:

  /**
   * @brief the pawn that has this sence
  */
  Controller* m_controller;
  
  /**
   * @brief the object that are relevant for this sence
  */
  vector<uint> m_tags;

  friend class Controller;
};

}


